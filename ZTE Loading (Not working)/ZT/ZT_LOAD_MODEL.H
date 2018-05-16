#ifndef ZT_LOAD_MODEL_H
#define ZT_LOAD_MODEL_H

#define MAX_MESHES (16)
#define MAX_MODELS (10)

/**Gouraud shading*/
#define	GRtbl(n)	    (0x1c38+(n))
#define	GRaddr	        0x1c38
#define GOUR_REAL_MAX   256

typedef struct
{
    unsigned short  TOTAL_MESH; //total amount of PDATA
    short           TOT_TEXT;  //total amount of textures
    unsigned int    TEXT_SIZE;  //to quickly load from disk, that's the size of the textures in bytes
    unsigned int    PDATA_SIZE; //to quickly load from disk, total size of pdata in bytes
    FIXED           Origin[XYZ]; //Origin point used to "center" the culling/collision data and your model's position. Should be 0,0,0 unless you have an offset
    FIXED           Length[XYZ];  //Lenght along the x,y z axis. Together with the origin, that gives you the bounding box for quick broad collision testing
} modelData_t;

typedef struct
{
    FIXED   pos[XYZ];
    FIXED   length[XYZ];
    Uint16  nbMeshes;
    Uint16  DUMMY;
    Uint32  DUMMY2;
    XPDATA * pol[MAX_MESHES];
} entity_t;

/**Store all your PDATA meshes here**/
extern entity_t entities[MAX_MODELS];

/** This function loads a 3d polygonal model. Returns the last address in LWRAM (to allow loading multiple meshes)**/
void *      ztLoad3Dmodel(Sint8 * filename, void * startAddress, entity_t * model,  bool UseRealtimeGouraud);

#endif // ZT_LOAD_MODEL_H
