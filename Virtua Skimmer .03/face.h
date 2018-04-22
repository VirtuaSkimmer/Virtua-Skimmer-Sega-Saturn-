/*
   3D model generated by Jo Map Editor v6.1
*/

#ifndef __3D_MODELFACE_H__
# define __3D_MODELFACE_H__

static POINT    PointGrp2[] =
{
	{698402, 1427283, 703516},
	{698402, 1427283, 703516},
	{-588186, 2479986, 555589},
	{410866, 3157759, -65453},
	{426402, 2261561, -64932},
	{-485323, 3142223, -61791},
	{-396828, 2246027, -61270},
	{372676, 2170053, 590162},
	{414518, 3200167, 681427},
	{-629932, 3276800, 671691},
	{-377336, 2123945, 424061},
	{-560727, 50697, -329376},
	{308882, 3143236, 834246},
	{291452, 3166744, 836865},
	{554323, 2626790, 676714},
};

static POLYGON    PolygonGrp2[] =
{
	{{-1302, -9514, 64828}, {8, 9, 2, 2}},
	{{-9514, 64828, 1127}, {4, 10, 6, 6}},
	{{64828, 1127, -63536}, {5, 8, 3, 3}},
	{{1127, -63536, -16027}, {6, 3, 4, 4}},
	{{-63536, -16027, -1149}, {3, 8, 14, 14}},
	{{-16027, -1149, 65420}, {2, 5, 6, 6}},
	{{-1149, 65420, -3708}, {10, 7, 2, 2}},
	{{65420, -3708, -290}, {7, 14, 2, 2}},
	{{-3708, -290, -43}, {14, 8, 2, 2}},
	{{-290, -43, -65535}, {4, 7, 10, 10}},
	{{-43, -65535, 63657}, {5, 9, 8, 8}},
	{{-65535, 63657, 15531}, {6, 5, 3, 3}},
	{{63657, 15531, -1193}, {7, 4, 14, 14}},
	{{15531, -1193, -62941}, {4, 3, 14, 14}},
	{{-1193, -62941, -6225}, {6, 10, 2, 2}},
	{{-62941, -6225, -17164}, {2, 9, 5, 5}},
};

static ATTR    AttributeGrp2[] =
{
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
	ATTRIBUTE(Dual_Plane, SORT_CEN, No_Texture, 0x801f, CL32KRGB | No_Gouraud, CL32KRGB | MESHoff, sprPolygon, No_Option),
};

jo_3d_mesh    MeshGrp2 =
{
	.data =
	{
		PointGrp2,
		15,
		PolygonGrp2,
		16,
		AttributeGrp2
	}
};

/* Call this function in you code to display all objects */
static __jo_force_inline void       display_face_mesh(void)
{
	jo_3d_mesh_draw(&MeshGrp2);
}

#endif /* !__3D_MODELFACE_H__ */
