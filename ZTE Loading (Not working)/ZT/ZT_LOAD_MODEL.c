#include "ZT_COMMON.H"

entity_t entities[MAX_MODELS];


/**
Modified to use Jo Engine
**/
void setTextures(Uint16 id, entity_t * model, unsigned int total_meshes, bool UseRealtimeGouraud)
{
    unsigned int i, ii;
    unsigned int gouraudCounter = 0;
    for (i=0; i< total_meshes; i++)
    {
        for (ii=0; ii<model->pol[i]->nbPolygon; ii++)
        {
            if (model->pol[i]->attbl[ii].dir & sprNoflip)
            {
                model->pol[i]->attbl[ii].texno+=id;
                model->pol[i]->attbl[ii].colno=LUTidx(model->pol[i]->attbl[ii].texno);
                if (UseRealtimeGouraud==true)
                {
                    if (model->pol[i]->attbl[ii].atrb & SPdis)
                    {
                        ATTR bufAttr = ATTRIBUTE(Single_Plane, SORT_CEN, model->pol[i]->attbl[ii].texno, model->pol[i]->attbl[ii].colno, GRtbl(gouraudCounter), Window_In|MESHoff|HSSon|ECdis|SPdis|CL16Look|CL_Gouraud, sprNoflip, UseGouraud|UseNearClip);
                        model->pol[i]->attbl[ii] = bufAttr;
                    }
                    else
                    {
                        ATTR bufAttr = ATTRIBUTE(Single_Plane, SORT_CEN, model->pol[i]->attbl[ii].texno, model->pol[i]->attbl[ii].colno, GRtbl(gouraudCounter), Window_In|MESHoff|HSSon|ECdis|SPenb|CL16Look|CL_Gouraud, sprNoflip, UseGouraud|UseNearClip);
                        model->pol[i]->attbl[ii] = bufAttr;
                    }
                    gouraudCounter++;
                }
            }
            else
            {
                if (UseRealtimeGouraud==true)
                {
                    ATTR bufAttr = ATTRIBUTE(Single_Plane, SORT_CEN, No_Texture, model->pol[i]->attbl[ii].colno, GRtbl(gouraudCounter), CL32KRGB|MESHoff|Window_In|CL_Gouraud, sprPolygon, UseGouraud|UseNearClip);
                    model->pol[i]->attbl[ii] = bufAttr;
                    gouraudCounter++;
                }
            }

        }
    }
}


Uint16 loadTextures(void * startAddress, modelData_t * modelData)
{
    int i;
    jo_texture_definition   *texture;
    jo_img *  pimg[modelData->TOT_TEXT];
    void * currentAddress = (void*)(startAddress+sizeof(modelData_t));
    int first_sprite = jo_get_last_sprite_id();

    for (i=0; i<modelData->TOT_TEXT; ++i)
    {
        pimg[i] = (jo_img *)currentAddress;
        currentAddress=(void*)(currentAddress+sizeof(jo_img));
        pimg[i]->width=pimg[i]->width/4;  //Quick and dirty way to get around the fact that Jo Engine doesn't support 4 bits pixel data.
        pimg[i]->data = (Uint16*)(currentAddress);
        currentAddress=(void*)(currentAddress+(sizeof(Uint16)*pimg[i]->width * pimg[i]->height));

        int id = jo_sprite_add(pimg[i]);

        /**Here we just fix the issue caused by using the add 8 bits image for 4 bits images**/
        texture=&__jo_sprite_def[id];
        texture->width=pimg[i]->width<<2;  //Ghetto technique for compatibility with Jo Engine, but trying to replace the sprite will throw an error
        __jo_sprite_pic[id].color_mode=COL_16;
        texture->size = JO_MULT_BY_32(texture->width & 0x1f8) | texture->height;
    }
    slDMACopy(currentAddress, (void*)(returnLUTaddr((Uint16)(first_sprite+1))), sizeof(Uint16)*16 * modelData->TOT_TEXT);
    slDMAWait();

    return (Uint16)(first_sprite+1);
}


void * loadPDATA(void * startAddress, entity_t * model, modelData_t * modelData)
{
    void * currentAddress = startAddress;
    unsigned int i;

    for (i=0; i<modelData->TOTAL_MESH; i++)
    {
        model->pol[i]=(XPDATA*)currentAddress;
        currentAddress=(void*)(currentAddress + sizeof(XPDATA));
        model->pol[i]->pntbl = (POINT*)currentAddress;
        currentAddress=(void*)(currentAddress + (sizeof(POINT)* model->pol[i]->nbPoint));
        model->pol[i]->pltbl = (POLYGON*)currentAddress;
        currentAddress=(void*)(currentAddress + (sizeof(POLYGON)* model->pol[i]->nbPolygon));
        model->pol[i]->attbl = (ATTR*)currentAddress;
        currentAddress=(void*)(currentAddress + (sizeof(ATTR)*model->pol[i]->nbPolygon));
        model->pol[i]->vntbl = (VECTOR*)currentAddress;
        currentAddress=(void*)(currentAddress + (sizeof(VECTOR)*model->pol[i]->nbPoint));
    }

    return currentAddress;
}

void * ztLoad3Dmodel(Sint8 * filename, void * startAddress, entity_t * model, bool UseRealtimeGouraud)
{
    memset_l((void*)startAddress,0x0000, (0xFFFE - ((Uint32)startAddress-(Uint32)LWRAM)));  //Not 100% necessary, since data can just be overwritten, but good for testing and see how much data a level takes
    void * currentAddress;
    currentAddress=startAddress;

    /**Load the file header and map data**/
    modelData_t bufModel; //If you wish to keep the model info elsewhere, you can do it
    void * ptr = &bufModel;
    Sint32 fid = GFS_NameToId((Sint8*)filename);
    GFS_Load(fid, 0, (Uint32 *)startAddress, (sizeof(modelData_t)));
    memcpy_l((Sint32*)ptr, (Sint32*)(startAddress), (sizeof(modelData_t)));

    /**ADDED**/
    model->pos[X]=bufModel.Origin[X]; model->pos[Y]=bufModel.Origin[Y]; model->pos[Z]=bufModel.Origin[Z];
    model->length[X]=bufModel.Length[X]; model->length[Y]=bufModel.Length[Y]; model->length[Z]=bufModel.Length[Z];
    model->nbMeshes=bufModel.TOTAL_MESH;

    /**Turns on the graphics (mainly for debugging)**/
    slScrAutoDisp(NBG3ON);
    slPrint("NOW LOADING...", slLocate(5, 5));    slPrint((char*)filename, slLocate(5, 6));
    fadeIn();

    /**Load the texture list (using an offset to allow DMA transfer)**/
    slPrint("LOADING TEXTURES", slLocate(5, 8));
    GFS_Load(fid, 0, (void*)startAddress, bufModel.TEXT_SIZE+(sizeof(modelData_t)));
    Uint16 first_texture = loadTextures(startAddress, &bufModel);


    /**Load PDATA**/
    slPrint("LOADING PDATA   ", slLocate(5, 8));
    Sint32 bytesOff = (bufModel.TEXT_SIZE+(sizeof(modelData_t)))/2048;
    GFS_Load(fid, bytesOff, (void*)startAddress, bufModel.PDATA_SIZE + 2048);
    bytesOff = bufModel.TEXT_SIZE+(sizeof(modelData_t)) - (bytesOff*2048);
    currentAddress = (void*)(currentAddress + bytesOff);

    currentAddress = loadPDATA((void*)currentAddress, model, &bufModel);


    /**Set textures**/
    slPrint("SETTING TEXTURES", slLocate(5, 8));
    setTextures(first_texture, model, bufModel.TOTAL_MESH, UseRealtimeGouraud);

    jo_clear_screen();

    fadeOut(0);

    return currentAddress;
}
