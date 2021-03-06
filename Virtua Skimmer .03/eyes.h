/*
   3D model generated by Jo Map Editor v6.1
*/

#ifndef __3D_MODELEYES_H__
# define __3D_MODELEYES_H__

static POINT    PointGrp8[] =
{
	{764362, 1562082, 769959},
	{764362, 1562082, 769959},
	{-613684, 55485, -360483},
	{-468740, 2882054, 998327},
	{-72719, 2882054, 998327},
	{-468740, 3276800, 966566},
	{-72719, 3276800, 966566},
	{77491, 2882054, 897504},
	{473512, 2882054, 897504},
	{77491, 3276800, 865743},
	{473512, 3276800, 865743},
};

static POLYGON    PolygonGrp8[] =
{
	{{0, 5255, 65324}, {4, 5, 3, 3}},
	{{0, 5255, 65324}, {8, 9, 7, 7}},
	{{5255, 65324, 0}, {4, 6, 5, 5}},
	{{65324, 0, 5255}, {8, 10, 9, 9}},
};

static ATTR    AttributeGrp8[] =
{
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
};

jo_3d_mesh    MeshGrp8 =
{
	.data =
	{
		PointGrp8,
		11,
		PolygonGrp8,
		4,
		AttributeGrp8
	}
};

/* Call this function in you code to display all objects */
static __jo_force_inline void       display_eyes_mesh(void)
{
	jo_3d_mesh_draw(&MeshGrp8);
}

#endif /* !__3D_MODELEYES_H__ */
