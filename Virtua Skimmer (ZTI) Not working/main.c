/*
** Jo Sega Saturn Engine
** Copyright (c) 2012-2017, Johannes Fetz (johannesfetz@gmail.com)
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Johannes Fetz nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL Johannes Fetz BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/***************************************************************************************************\
** Special Note : The 3D part on Jo Engine is still in development. So, some glitch may occur ;)
**                Btw, texture mapping for triangle base mesh (not quads) is experimental.
\***************************************************************************************************/

#include <jo/jo.h>
#include "ZT/ZT_COMMON.h"
//#include "model.h"
//#include "sonic.h"
#include "foam.h"
#include "board.h"
#include "hair.h"
//#include "face.h"
//#include "body.h"
//#include "trunks.h"
//#include "legs.h"
#include "bandana.h"
//#include "eyes.h"


/**Added by XL2 to use my own CD loading functions**/
#define     OPEN_MAX    (Sint32)5
#define     DIR_MAX     (Sint32)25
#define     RD_UNIT     (10)
#define     SECT_SIZE   (2048)
GfsDirTbl gfsDirTbl;
GfsDirName gfsDirName[DIR_MAX];
Uint32 gfsLibWork[GFS_WORK_SIZE(OPEN_MAX)/sizeof(Uint32)];
Sint32 gfsDirN;
void    ztCDinit(void)
{
    GFS_DIRTBL_TYPE(&gfsDirTbl) = GFS_DIR_NAME;
    GFS_DIRTBL_DIRNAME(&gfsDirTbl) = gfsDirName;
    GFS_DIRTBL_NDIR(&gfsDirTbl) = DIR_MAX;
    gfsDirN = GFS_Init(OPEN_MAX, gfsLibWork, &gfsDirTbl);
}
/**End of added function**/






static jo_camera    cam;
static float        rx, ry;
static float        qx, qy;
static float        fx, fy;
//Wave Speed
static float        wave_pos_x = -10;
static float        water_rot_x = -90;
//static float        sonic_pos_x = 80;
//Main Game Controls(No Player control until reset)
static bool         fall = false;
static bool         start = true;
//Bool to change players hair
static bool         hairchange = true;
static bool         wavehit = false;
//NiGHTS Style Grade Animation
static int ring_anim_id = 0; 	

static bool         use_screen_doors;
static bool         use_light = true;
static bool         use_texture = true;
static unsigned int selected_polygon_index = 0;
static unsigned int Score = 0;



Sint32 framerate;

jo_vertice          plane_vertices[] = JO_3D_PLANE_VERTICES(104);
jo_vertice          plane2_vertices[] = JO_3D_PLANE_VERTICES(104);
jo_vertice          plane3_vertices[] = JO_3D_PLANE_VERTICES(104);

//Water
jo_3d_quad          plane;
//Beach
jo_3d_quad          plane2;
//DitheredWater
jo_3d_quad          plane3;

 //Score = 0;

 sonic_pos_x = 80;
 sonic_pos_y = -4;
 sonic_pos_z = 50;
 sonic_rot_x = 00;
 sonic_rot_y = 0;
 sonic_rot_z = 180;
 //used to stop sonics movement end of wave
 sonic2_pos_x =0;
 //wave_pos_x = -170;
 //wave_pos_x = -10;
 wave_pos_y = 0;
 wave_pos_z = -16;
 cam_pos_x = 85;
 cam_pos_y = -25;
 cam_pos_z = 90;
 skim_rot_x = 0;
 skim_rot_y = 0;
 skim_rot_z = 0;
 skim2_rot_x = -90;
 skim2_rot_y = 0;
 skim2_rot_z = 0;
 skim_pos_x = 80;
 skim2_pos_x = 0;
 skim_pos_y = -9;
 skim_pos_z = 54;
 skim2_pos_z = 51;
  skim3_pos_z = 54;
 

 
 //water_rot_x = -90;
 
 beach_pos_x = 22;
 beach_pos_y = 21;
 beach_pos_z = -12;
 
 tree_pos_x = 75;
 tree_pos_y = -0;
 tree_pos_z = -40;
  
 
 //Ocean
void                create_plane(void)
{
    jo_3d_create_plane(&plane, plane_vertices);
    jo_3d_set_texture(&plane, 3);
   
	
}
// Beach
void                create_plane2(void)
{
    jo_3d_create_plane(&plane2, plane2_vertices);
    jo_3d_set_texture(&plane2, 4);


	
}

// Dither Ocean
void                create_plane3(void)
{
    jo_3d_create_plane(&plane3, plane3_vertices);
    jo_3d_set_texture(&plane3, 9);
	
   // jo_3d_set_transparency(&plane3, true);

	
	 //if (jo_is_pad1_key_pressed(JO_KEY_B))
    //{
	   // jo_3d_set_texture(&plane3, 9);
        
        
    //}
	//else
           // jo_3d_set_texture(&plane3, 10);
	
}




void			    my_draw(void)
{
    
  

    //jo_printf(12, 1, "*Virtua Skimmer");
	
    jo_3d_camera_look_at(&cam);
		jo_3d_camera_set_viewpoint 	(&cam,cam_pos_x,cam_pos_y,cam_pos_z);  
		
		//Wave 3D Model
    jo_3d_push_matrix();
    {
	    jo_3d_translate_matrix 	( wave_pos_x,wave_pos_y,wave_pos_z );
        jo_3d_rotate_matrix_rad_x(rx);
        jo_3d_rotate_matrix_rad_y(ry);
		jo_3d_rotate_matrix_z 	( 	180	) 	;
		jo_3d_rotate_matrix_y 	( 	-190	) ;
		jo_3d_rotate_matrix_x 	( 	0) ;
		
		//Start wave movement
		wave_pos_x += 1;
		//Stop wave movement
		if (wave_pos_x> 65)
	     {
	      wave_pos_x = 65;
	     }
		
		/*Auto Skim movement
		if (sonic_pos_x < 65 && start == false)
	     {
	      sonic_pos_x -= 1;
	     }
		*/
		
		//DEMO MODE INTRO
		
		if (start==true && wave_pos_x > 40)
		{
		wave_pos_x = 40;
		sonic_pos_x = 40;
		skim_rot_y += 10;
	    sonic_rot_y -=10;
		
		}
		if (start==true)
		{
		sonic_pos_x -= 1;
		 
		}
		if (start==true && sonic_pos_x < 60)
		{
		skim_rot_y -= 10;
	    sonic_rot_y +=10;
		
		}
		
		
		
		
		
        /* Use Jo Map Editor (v5.0 or superior) to convert mesh for the Sega Saturn */
		jo_3d_set_scalef(.9,.9,.9) ;
		 jo_3d_display_level(7);
        //display_workingwave_mesh();
		 
		
    }
	//jo_3d_set_scale ( 100,100,100);
    jo_3d_pop_matrix();
	
	
	
	
	
	
	
	
	
	
	draw_player();
    draw_floor();
	draw_beach();
	draw_sprites();
    draw_foam();
	draw_3dfoam();
	draw_dithwater();
	draw_skimboard();

	
	
	if (start == true)
	{
	draw_title();
	draw_demo();
	draw_controls();
	 
	
	}
	if (start == true && wave_pos_x > 39)
	{
	
	draw_startpress();
	
	
	}
	
	
	if(fall == true)
	{
	jo_sprite_draw3D(jo_get_anim_sprite(ring_anim_id), 100  , 25 , 30 );
	 //jo_restart_sprite_anim (ring_anim_id);
	draw_wipeout();
	draw_splash();
	}
	//jo_printf(27, 14, "[Score (%d)", Score) ;

    //jo_printf_with_color(0, 24,JO_COLOR_INDEX_Red, "[PAD] move player");
   // jo_printf(0, 25, "[L/R] select polygon (index=%d)  ", selected_polygon_index);
    //jo_printf(0, 26, "[C] to back ocean wave up (%s) ", use_texture ? "hold" : "off");
   // jo_printf(0, 27, "[B] to toggle light (%s) ", use_light ? "on" : "off");
    //jo_printf(0, 28, "[A] to advance ocean wave(%s) ", use_screen_doors ? "hold" : "off");
	
    if (wave_pos_x > 50)
	{
	jo_sprite_draw3D(jo_get_anim_sprite(ring_anim_id), 100  , 25 , 30 );
	}


	
	//Score Display 
	if (wave_pos_x > 64)
	{
	jo_printf(27, 14, "[Score (%d)", Score) ;
	
	 //Grade
	 if (Score >= 0 && Score < 99 )
	 {
	  jo_printf(27, 15, "[GRADE(F)") ;
	  jo_stop_sprite_anim (ring_anim_id);
	 jo_set_sprite_anim_frame (ring_anim_id, 8);
	 	
	 }
	 if (Score > 100)
	 {
	  jo_printf(27, 15, "[GRADE(F)") ;
	  jo_set_sprite_anim_frame (ring_anim_id, 1);
	 }
	  if (Score > 500 && Score < 999)
	   
	 {
	  jo_printf(27, 15, "[GRADE(C)") ;
	  jo_stop_sprite_anim (ring_anim_id);
	 jo_set_sprite_anim_frame (ring_anim_id, 2);
	 }
	if (Score > 1000 && Score < 1599)
	 {
	  jo_printf(27, 15, "[GRADE(B)") ;
	  jo_set_sprite_anim_frame (ring_anim_id, 4);
	 }
	 if (Score > 1600)
	 {
	  jo_printf(27, 15, "[GRADE(A)") ;
	  jo_stop_sprite_anim (ring_anim_id);
	 jo_set_sprite_anim_frame (ring_anim_id, 6);
	 }
	   //draw_fgrade();
	
	}
	
	if (wave_pos_x < 64)
	{	
	if (selected_polygon_index > 20)
	{
	Score += 1;
	jo_printf(7, 10, "BS180 x1.2 %d", Score) ;
	}
	
	if (selected_polygon_index > 40)
	{
	Score += 2;
	jo_printf(7, 10, "BS360 x1.4 %d", Score);
	}
	if (selected_polygon_index > 60)
	{
	Score += 3;
	jo_printf(7, 10, "BS540 x1.5 %d", Score);
	}
	if (selected_polygon_index > 80)
	{
	Score += 4;
	jo_printf(7, 10, "BS720 x2 %d", Score);
	}
	if (selected_polygon_index > 100)
	{
	Score += 5;
	jo_printf(7, 10, "BS1080 x3 %d", Score);
	}
	
	if (sonic_rot_x < -180)
	{
	Score += 10;
	jo_printf(22, 10, "Backflip x1.2 %d", Score);
	}
	
	if (sonic_pos_x < wave_pos_x)
	{
       if (sonic_pos_z > 60)
       {	
          Score += 10;	   
	jo_printf(22,12, "Barrel x1.2 %d", Score);
	   }
	}
		}
	
		
	
	
	//slPrint("Framerate : ", slLocate(0, 22));
    //slPrintFX(toFIXED(60/framerate), slLocate(10,22));
	
	 
}

void            apply_effect(void)
{
    jo_3d_set_mesh_screen_doors(&plane3, use_screen_doors);
	 
    //jo_3d_set_mesh_light(&Meshwaveattemt2COMwave17821Material1, use_light);
	
	//jo_3d_set_mesh_light(&MeshGrp2, use_light);
	//jo_3d_set_mesh_light(&MeshGrp3, use_light);
	//jo_3d_set_mesh_light(&MeshGrp5, use_light);
	
   
	 	//Deleted turn off textures
		
		 
		
		if ( hairchange == true) 
		{
		jo_3d_set_mesh_texture(&MeshGrp, 20);
		jo_3d_set_mesh_texture(&MeshGrp7, 21);
		//jo_3d_set_mesh_texture(&MeshGrp2, 22);
		//jo_3d_set_mesh_texture(&MeshGrp3, 22);
		//jo_3d_set_mesh_texture(&MeshGrp5, 22);
		}
		
		if ( hairchange == false) 
		{
		jo_3d_set_mesh_texture(&MeshGrp, 18);
		jo_3d_set_mesh_color (&MeshGrp7, 6);
		//jo_3d_set_mesh_texture(&MeshGrp2, 19);
		//jo_3d_set_mesh_texture(&MeshGrp3, 19);
		//jo_3d_set_mesh_texture(&MeshGrp5, 19);
		}
		
	

        //jo_3d_set_mesh_texture(&Meshwaveattemt2COMwave17821Material1, 0);
		//jo_3d_set_mesh_texture(&MeshGrp, 18);
		
		//jo_3d_set_mesh_color (&MeshGrp7, 6);
		//jo_3d_set_mesh_color (&MeshGrp8, 1);
		//jo_3d_set_mesh_color (&MeshGrp2, 3);
		//jo_3d_set_mesh_color (&MeshGrp3, 2);
		//jo_3d_set_mesh_color (&MeshGrp4, 14);
		//jo_3d_set_mesh_color (&MeshGrp5, 80);
		jo_3d_set_mesh_texture(&MeshPlane, 11);
		
		
		jo_3d_set_mesh_screen_doors(&Meshwaveattemt2COMwave17821Material1001, use_screen_doors);
        jo_3d_set_mesh_texture(&Meshwaveattemt2COMwave17821Material1001, 8);
		
		

}

void                draw_player(void)
{

//Player 3D model	
	//hair
	
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y,sonic_pos_z );
		 	jo_3d_set_scalef(.35,.35,.35) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  jo_3d_display_level(7);
		display_hair_mesh();
	
    }
    jo_3d_pop_matrix();
	
	//face
	
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.25,.25,.25) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		//display_face_mesh();
	
    }
    jo_3d_pop_matrix();
	
	//body
	
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.17,.17,.17) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		//display_body_mesh();
	
    }
    jo_3d_pop_matrix();
	
	//trunks
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.28,.25,.28) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		//display_trunks_mesh();
	
    }
    jo_3d_pop_matrix();
	
	//legs
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.10,.10,.10) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		//display_legs_mesh();
	
    }
    jo_3d_pop_matrix();
	
	//bandana
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.28,.28,.28) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		display_bandana_mesh();
	
    }
    jo_3d_pop_matrix();
	
		//eyes
	jo_3d_push_matrix();
    {
	  
         
		jo_3d_translate_matrix 	( sonic_pos_x,sonic_pos_y ,sonic_pos_z );
		 	jo_3d_set_scalef(.24,.24,.24) ;
        jo_3d_rotate_matrix_z 	( 	sonic_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	sonic_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	sonic_rot_x	) ;
		//jo_3d_rotate_matrix_rad_z(qx);
	  //jo_3d_rotate_matrix_rad_y(qy);
	  //jo_3d_display_level(5);
		//display_eyes_mesh();
	
    }
    jo_3d_pop_matrix();
	
	
	





}





//The 3D dithered foam along the crest of the wave
void                draw_3dfoam(void)
{
    jo_3d_push_matrix();
    {
	 jo_3d_translate_matrix 	( wave_pos_x- 6,wave_pos_y + 15,wave_pos_z -46  );
        
		jo_3d_rotate_matrix_z 	( 	180	) 	;
		jo_3d_rotate_matrix_y 	( 	-190	) ;
		jo_3d_rotate_matrix_x 	( 	0) ;
		
		jo_3d_display_level(3);
        /* Use Jo Map Editor (v5.0 or superior) to convert mesh for the Sega Saturn */
		jo_3d_set_scalef(.75,.75,.75) ;
        display_foam_mesh();
	
	
    }
    jo_3d_pop_matrix();
}

void                draw_skimboard(void)
{
    jo_3d_push_matrix();
    {
	 jo_3d_translate_matrix 	( sonic_pos_x,skim_pos_y - 5,skim_pos_z);
        
		jo_3d_rotate_matrix_z 	( 	skim_rot_z	) ;
		jo_3d_rotate_matrix_y 	( 	skim_rot_y	) ;
		jo_3d_rotate_matrix_x 	( 	skim_rot_x	) ;
		
		
		if (sonic_pos_x >  65 )
		{
		
		//skim_rot_x = 0;
		skim_rot_x = skim2_rot_x;
		
		}
		else
		skim_rot_x = skim_rot_x;
		
		
		
		
			
		jo_3d_display_level(3);
        /* Use Jo Map Editor (v5.0 or superior) to convert mesh for the Sega Saturn */
		jo_3d_set_scalef(.10,.15,.15) ;
        display_board_mesh();
	
	
    }
    jo_3d_pop_matrix();
}


//Ocean Floor
void                draw_floor(void)
{
    jo_3d_push_matrix();
    {
	jo_3d_translate_matrix 	( -15,-22,10);
	
	//jo_3d_set_scalef(1.7,1,2.5) ;
	//jo_3d_rotate_matrix_rad_x(fx);
       // jo_3d_rotate_matrix_rad_y(fy);
	    
        jo_3d_rotate_matrix_x(-90);
		jo_3d_rotate_matrix_z(0);
		jo_3d_rotate_matrix_y(0);
        jo_3d_draw(&plane);
    }
    jo_3d_pop_matrix();
}


//Beach
void                draw_beach(void)
{
    jo_3d_push_matrix();
    {
	jo_3d_translate_matrix 	( beach_pos_x,beach_pos_y,beach_pos_z);
	
		
	    jo_3d_set_scalef(1,1,1.2) ;
       jo_3d_rotate_matrix_x(78);
		jo_3d_rotate_matrix_z(0);
		jo_3d_rotate_matrix_y(0);
        jo_3d_draw(&plane2);
  }
    jo_3d_pop_matrix();
}


//Dithered Ocean 
void                draw_dithwater(void)
{
    jo_3d_push_matrix();
    {
	jo_3d_translate_matrix 	( -15,-22,10);
	
	//jo_3d_set_scalef(1.7,1,2.5) ;
	
	
	//Dithred Water movement
	
	if (water_rot_x< -94)
	{
	water_rot_x += .2f;
	
	}
	else 
	
	water_rot_x -= .1f;
	
	    
        jo_3d_rotate_matrix_x( water_rot_x);
		jo_3d_rotate_matrix_z(0);
		jo_3d_rotate_matrix_y(0);
        jo_3d_draw(&plane3);
    }
    jo_3d_pop_matrix();
}

//Beach Tree
void			draw_sprites()
{
    // jo_sprite_change_sprite_scale 	( 	.2	);
	 jo_3d_push_matrix();
    {
	    jo_3d_rotate_matrix_rad_x(fx);
       jo_3d_rotate_matrix_rad_y(fy);
       jo_3d_rotate_matrix_x(-20);
        jo_3d_draw_sprite_at(5, tree_pos_x, tree_pos_y, tree_pos_z);
        //jo_sprite_draw3D_and_rotate 	( 5, 0,0,0,90) 	
    }
    jo_3d_pop_matrix();
}

//The circle foam sprites 
void			draw_foam()
{
     //jo_sprite_change_sprite_scale 	( 	.2	);
	 jo_3d_push_matrix();
    {
	   jo_3d_display_level(5);
	   jo_3d_set_transparency(jo_3d_get_sprite_quad(7), true);
       jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(90);
        jo_3d_draw_sprite_at(7, wave_pos_z - 63   , wave_pos_y -8, wave_pos_x + 10 );
        //jo_sprite_draw3D_and_rotate 	( 5, 0,0,0,90) 	
    }
    jo_3d_pop_matrix();
}

//Fall Splash sprite
void			draw_splash()
{
     //jo_sprite_change_sprite_scale 	( 	.2	);
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	  // jo_3d_rotate_matrix_y(90);
	   	
        jo_3d_draw_sprite_at(12, sonic_pos_x   , sonic_pos_y -5 , sonic_pos_z  );
        
    }
    jo_3d_pop_matrix();
}

//wipeout sprite
void			draw_wipeout()
{
     //jo_sprite_change_sprite_scale 	( 	.2	);
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(35); 
	   	
        jo_3d_draw_sprite_at(13, -20  , -40 , -5 );
        
    }
    jo_3d_pop_matrix();
}

//Title Screen sprite
void			draw_title()
{
     //jo_sprite_change_sprite_scale 	( 	.2	);
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(35); 
	   	
        jo_3d_draw_sprite_at(14, -25  , -40 , -5 );
        
    }
    jo_3d_pop_matrix();
}

//Press start title screen gui
void			draw_startpress()
{
     //jo_sprite_change_sprite_scale 	( 	.5	);
	 
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(42); 
	   	
        jo_3d_draw_sprite_at(15, 50  , 15 , 30 );
        
    }
    jo_3d_pop_matrix();
}

//DEMO words title screen gui
void			draw_demo()
{
     //jo_sprite_change_sprite_scale 	( 	.5	);
	 
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(42); 
	   	
        jo_3d_draw_sprite_at(17, -55  , 65 , 30 );
        
    }
    jo_3d_pop_matrix();
}

//Control screen during intro
void			draw_controls()
{
     //jo_sprite_change_sprite_scale 	( 	.8	);
	 jo_3d_push_matrix();
    {
	   //jo_3d_display_level(5);
	
       //jo_3d_rotate_matrix_x(0);
	   jo_3d_rotate_matrix_y(42); 
	   	
        jo_3d_draw_sprite_at(16, 40  , 55 , 30 );
        
    }
    jo_3d_pop_matrix();
}




 


/*
void            my_background()
{
    jo_img      bg;

    bg.data = NULL;
    jo_tga_loader(&bg, "BG", "BG.TGA", JO_COLOR_Transparent);
    jo_set_background_sprite(&bg, 0, 0);
    jo_free_img(&bg);
}
*/


void			my_gamepad(void)
{
//Test values display
//jo_printf(8,19, "PlayerPOSZ %d", sonic_pos_z);
//jo_printf(8,20, "PlayerPOSX %d", sonic_pos_x);
//jo_printf(8,21, "PlayerPOSY %d", sonic_pos_y);


//Barrel Fall
if( sonic_pos_z > 74 && sonic_pos_x == wave_pos_x && sonic_pos_y == -10)
{
 fall = true;
 //jo_printf(12, 1, "**TOO HIGH UP IN BARREL**");
}
//Barrel Fall Duck
if( sonic_pos_z > 76 && sonic_pos_x == wave_pos_x && sonic_pos_y == -4)
{
 fall = true;
 //jo_printf(12, 1, "**DUCK DEEP IN BARREL!**");
}
if( sonic_pos_z > 85 && sonic_pos_x == wave_pos_x)
{
 fall = true;
 //jo_printf(12, 1, "**DUCK DEEP IN BARREL!**");
}

//KickFlip C button fall
if ( skim_rot_x < -90 && jo_is_pad1_key_pressed(JO_KEY_C) == false && skim_rot_x < -450 || skim_rot_x < -90 && jo_is_pad1_key_pressed(JO_KEY_C) == false && skim_rot_x > -300 )
{
  fall = true;
  //jo_printf(12, 1, "**NOT ENOUGH FLIP  **");
}
//Reset Succesful Kickflip Rotation
if ( jo_is_pad1_key_pressed(JO_KEY_C) == false && skim_rot_x > -450 && skim_rot_x < -300)
{
   skim_rot_x = -90;
}

//BackFlip B button fall
if ( sonic_rot_x < -1 && jo_is_pad1_key_pressed(JO_KEY_B) == false && sonic_rot_x < -400 || sonic_rot_x < -1 && jo_is_pad1_key_pressed(JO_KEY_B) == false && sonic_rot_x > -300 )
{
  fall = true;
  //jo_printf(12, 1, "**NOT ENOUGH ROTATION**");
}
//Reset Succesful Kickflip Rotation
if ( jo_is_pad1_key_pressed(JO_KEY_B) == false && sonic_rot_x > -400 && sonic_rot_x < -300)
{
   sonic_rot_x = 0;
    skim_rot_x = -90;
}

/*
//Shuv it A button fall
if ( skim_rot_y < -1 && jo_is_pad1_key_pressed(JO_KEY_A) == false && skim_rot_y < -420 || skim_rot_y < -1 && jo_is_pad1_key_pressed(JO_KEY_A) == false && skim_rot_y > -300 )
{
  fall = true;
}


//Reset Succesful Shuvit Rotation
if ( jo_is_pad1_key_pressed(JO_KEY_A) == false && skim_rot_y > -420 && skim_rot_y < -300)
{
   skim_rot_y = 0;
}
*/





 //Gravity 
	  if(sonic_pos_y = -4)
	   {
	     sonic_pos_y -= .5f;
	   }
	   else
	   sonic_pos_y +=.5f;
	   
	   if(skim_pos_y = -4)
	   {
	     skim_pos_y -= .5f;
	   }
	   else
	   skim_pos_y +=.5f;
	   
	   //Wave Collision
	   if (sonic_pos_x < wave_pos_x)
	   {
	       sonic_pos_x = wave_pos_x +1 ;
	   }
	   
	   //Skimboard postion from stand to surf
	  
	   if (sonic_pos_x >  67 )
		{
	      skim_pos_y = -4;
		  skim_pos_z = skim3_pos_z;
		  
		  }
		   if (sonic_pos_x <  67 )
		{
	      skim_pos_y = 1;
		  skim_pos_z = skim2_pos_z;
		  }
		  
		  //FALLING & NO CONTROL & END RUN
		  
		  //Wave hits end
		  if (wave_pos_x == 65 )
		  {
		
		  }
		
		  
		  //Player Falling
		  if (fall == true)
		  {
		   sonic_rot_x +=10;
		   sonic_rot_z +=10;
		   sonic_rot_y +=10;
		   Score = 0;
		  }
		  
		  
		  
		  
		  
 
if (fall == false && wave_pos_x < 65)

	{		  
		  

    if (jo_is_pad1_key_pressed(JO_KEY_UP))
	{
	   	
	     sonic_pos_z -= 1;
	     skim_pos_z -= 1;
		 skim2_pos_z -= 1;
		 skim3_pos_z -= 1;
        //fx -= 0.01f;
		
		}
    if (jo_is_pad1_key_pressed(JO_KEY_DOWN))
	{   
	
	    sonic_pos_z += 1;
		skim_pos_z  +=1;
		skim2_pos_z += 1;
		skim3_pos_z += 1;
        //fx += 0.01f;
		
		}
    if (jo_is_pad1_key_pressed(JO_KEY_LEFT))
	{	
		//skim_pos_x += 2;
	    sonic_pos_x += 1;
		
		}
		
     if (jo_is_pad1_key_pressed(JO_KEY_RIGHT))
	 {
	 
	 //This changes the right key to surf up and down the wave instead move right
			if (sonic_pos_x <= wave_pos_x + 1)
			{
	     sonic_pos_y -= 6.5f;
	     skim_pos_y -= 6.5f;
			}
			else
			sonic_pos_x -= 1;
			
	     }
		    if (jo_is_pad1_key_pressed(JO_KEY_L))
    {
		
	 //fall = true;
	//fx -= 0.01f;
		 //skim_rot_y += 10;
	    //sonic_rot_y -=10;
        //if (selected_polygon_index > 0)
          //  --selected_polygon_index;
        //else
           // selected_polygon_index = jo_3d_get_mesh_polygon_count(&Meshwaveattemt2COMwave17821Material1) - 1;
       // apply_effect();
    }
	
    if (jo_is_pad1_key_pressed(JO_KEY_R) && sonic_pos_x < 65 && start == false )
    {
	//fx += 0.01f;
		 skim_rot_y -= 10;
	    sonic_rot_y +=10;
		//wave_pos_x += 2;
        //++selected_polygon_index;
       // if (selected_polygon_index >= jo_3d_get_mesh_polygon_count(&Meshwaveattemt2COMwave17821Material1))
           // selected_polygon_index = 0;
        //apply_effect();
    }
	
	// Ending bracket for wave being <65
	}
		
		//jo_printf(8,19, "Sskimrot %d", skim_rot_y);
    if (jo_is_pad1_key_pressed(JO_KEY_A)&& sonic_pos_x < 65 && start == false )
    {
	
		//Shuvit
		sonic_pos_y -= 5.5f;
        skim_rot_y -= 17;
		jo_printf(22,11, "Shuv it x1.2 %d", Score);
		Score += 10;
    }
	
	//jo_printf(8,18, "SkimY %d", skim_pos_y);
	//jo_printf(8,19, "Sonicrot %d", sonic_rot_x);
    if (jo_is_pad1_key_pressed(JO_KEY_B) && start ==false )
    {
       if (sonic_pos_y < -8)
{	   
       //Backflip
	  sonic_pos_y -= 10.5f;
	  skim_pos_y -= 10.5f;
	  sonic_rot_x -= 18;
	  skim_rot_x += 18;	
}	  
    }
	
	
	//jo_printf(8,18, "SkimY %d", skim_pos_y);
	//jo_printf(8,19, "Skimrot %d", skim_rot_x);
    if (jo_is_pad1_key_pressed(JO_KEY_C) && sonic_pos_x < 65 && start == false )
    {
	   //Kickflip
	     sonic_pos_y -= 8.5f;
	     skim_rot_x -= 17.5f;
		 skim_pos_y -= 4.5f;
		 jo_printf(8,11, "Kickflip x1.2 %d", Score);
		Score += 10;
    }
	else
	//skim_rot_x = skim_rot_x;
	
	
	if(sonic_pos_z > 65 && sonic_pos_x == wave_pos_x)
{
wavehit=true;
}	

	if (jo_is_pad1_key_pressed(JO_KEY_X) && wavehit==true && start == false )
    {
	  sonic_pos_y+=4.5f;
    }
	
	
	
	    if (jo_is_pad1_key_pressed(JO_KEY_Z))
    {
	  hairchange = true;
	   apply_effect();
    }
    if (jo_is_pad1_key_pressed(JO_KEY_Y))
    {
	  hairchange = false;
	   apply_effect();
    }
	
	 if (jo_is_pad1_key_down(JO_KEY_START))
    {
		//Restart Game
	    wave_pos_x = -110;
		skim_rot_x = 0;
	skim_rot_y = 0;
	sonic_rot_x = 0;
	sonic_rot_y = 0;
	sonic_pos_x = 80;
    sonic_pos_y = -4;
    sonic_pos_z = 50;
	skim_pos_x = 80;
    skim_pos_y = -9;
    skim_pos_z = 54;
	skim2_pos_x = 0;

    skim2_pos_z = 51;
    skim3_pos_z = 54;
	
	sonic_rot_z =180;
	 fall = false;
	 start = false;
     wavehit = false;
    }
	
 
	
	
	
	
	
	
	
	
	
	
	
	
}


//NiGHTS Style Grade Animation
void			create_ring_sprite_animation()
{
	/* It's quite simple to create an animation.
 	   First, you have to load all sprites
	*/
	 jo_sprite_change_sprite_scale 	( 	1.3	);
	int twenty_sprite_id = jo_sprite_add_image_pack("RING", "RING.TEX", JO_COLOR_Transparent);
	/* Then, you create the animation by giving the first sprite Id, the total of sprites, and the framerate */
	ring_anim_id = jo_create_sprite_anim(twenty_sprite_id, 9, 2);
	/* Finally, you chose the type of animation you wants => next step in my_draw() */
	jo_start_sprite_anim_loop(ring_anim_id);
}

void  targa(void)
{

	
    jo_sprite_add_tga(JO_ROOT_DIR, "ROCK.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "SONIC.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "FLR.TGA", JO_COLOR_Transparent);
	  jo_sprite_add_tga(JO_ROOT_DIR, "BOX.TGA", JO_COLOR_Transparent);
	  jo_sprite_add_tga(JO_ROOT_DIR, "BEACH.TGA", JO_COLOR_Transparent);
	  jo_sprite_add_tga(JO_ROOT_DIR, "COY.TGA", JO_COLOR_Blue);
	  jo_sprite_add_tga(JO_ROOT_DIR, "SKIM.TGA", JO_COLOR_Green);
	  jo_sprite_add_tga(JO_ROOT_DIR, "FOAM.TGA", JO_COLOR_Green);
	    jo_sprite_add_tga(JO_ROOT_DIR, "FOAM3D.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "FLRDITH.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "FLRDITHF.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "BOARD.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "SPLASH.TGA", JO_COLOR_Green);
		jo_sprite_add_tga(JO_ROOT_DIR, "WIPEOUT.TGA", JO_COLOR_Green);
        jo_sprite_add_tga(JO_ROOT_DIR, "TITLE.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "START.TGA", JO_COLOR_Transparent);
		jo_sprite_add_tga(JO_ROOT_DIR, "CONTROLS.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "DEMO.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "HAIR.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "SKIN.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "HAIR2.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "BANDANA.TGA", JO_COLOR_Transparent);
	jo_sprite_add_tga(JO_ROOT_DIR, "SKIN2.TGA", JO_COLOR_Transparent);

}




extern Sint8 SynchConst;
void			jo_main(void)
{
	jo_core_init(JO_COLOR_Blue);
	
/**Added by XL2 : turns off the TV while we load data**/
    slTVOff();
    /****/
	
	slDynamicFrame(ON); //Dynamic framerate, when the VDP1 can't fully draw to the framebuffer in the allocated amount of time (1/60, 2/60, etc.) it will continue drawing when it's ON. Else it will try to complete drawing by skipping lines and details and finish in the allocated time. If the app runs well with the value at OFF, leave it at OFF!
    SynchConst=(Sint8)2;  //Framerate control. 1/60 = 60 FPS, 2/60 = 30 FPS, etc.
	framerate=2;

   //add tga
   targa();
	
	//NiGHTS style Grade Animation
   create_ring_sprite_animation();
   

	
	create_plane3();
	create_plane2();
	create_plane();
	//my_background();
	
		/**XL2**/

	ztCDinit(); /**Reinit the CD functions using my own. Might break Jo Engine loading functions*/
    ztFont2NBG3();  /**Swaps the NBG0 to NBG3 (NBG0 is much more flexible, so we use NBG3 for text only)**/
    memset_w((Sint16*)(VDP2_VRAM_A0), 0x0000, 262144);
    ztLoadVDP2bmp("NBG0.ZTI", (Uint16*)(VDP2_VRAM_A1), 1, bmNBG0);  /** Just to show you how to use the NBG0 with my custom function **/
    fadeIn();

    /**Leave some time to show the splash screen**/
    int i=0;
    while (i<60*4){
        i+=2; slSynch();
    }

    fadeOut(1); /**Again just to show you, it clears the BG when you put (1), else it keeps it (0) **/
    ztLoadVDP2bmp("BEACH.ZTI", (Uint16*)(VDP2_VRAM_A0), 3, bmNBG1); /**Loads the Beach to NBG1**/
    slScrPosNbg1(toFIXED(0.0), toFIXED(50.0)); //Offset the background here
	

    slScrPosNbg1(toFIXED(0.0), toFIXED(50.0)); //Offset the background here
	
    jo_3d_camera_init(&cam);
	
    jo_core_add_callback(my_gamepad);
	jo_core_add_callback(my_draw);
	use_screen_doors ^= true;
	apply_effect();
	
   fadeIn();/**Smooth fade in**/

	
	jo_core_run();
	
	  
}

/*
** END OF FILE
*/
