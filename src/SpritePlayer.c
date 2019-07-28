#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "ZGBMain.h"
#include "Print.h"
#include "rand.h"
#include "Sound.h"

//The first number indicates the number of frames
const UINT8 anim_walk_left[] = {2, 0, 1};
const UINT8 anim_walk_up[] = {2, 2, 3};
const UINT8 anim_walk_right[] = {2, 4, 5};
const UINT8 anim_walk_down[] = {2, 6, 7};


const UINT8 speed[] = { 32, 24, 16, 10, 9, 8, 7, 6 };

const UINT8 MAX_SPEED_IDX = 6;

const UINT8 MAX_TAIL_LEN = 251;
const UINT8 ROWS = 18;
const UINT8 COLUMNS = 20;

INT8 dir_xy[] = { 1, 0 };
UINT8 dir = 8;

INT8 move = 0;
UINT8 speed_idx = 0;

UINT8 tailX[251];
UINT8 tailY[251];
UINT8 tail_len = 0;

UINT8 head_tilepos[2];
UINT8 tail_tilepos[2];
UINT8 tail_end[2];

UINT8 fruitx;
UINT8 fruity;

//UINT8 wait = 0;

#define VRAM    (*(__REG)0x9800)    /* VRAM register */

//UINT16* VRAM = 0x9800;

struct Sprite* fruit_spr; 

extern UINT8 available_fruits[14][18];

extern UINT16 score;

void spawn_fruit( )
{
	for( UINT8 i = 0; i != 14; ++i )
	{
		for( UINT8 j = 0; j !=  18; ++j )
		{
			if( available_fruits[i][j] )
			{
				fruity = i + 1;
				fruitx = j + 1;
	
				/*	
				DPRINT_POS(11, 0);
				DPrintf("x: %i ", fruitx );
				DPRINT_POS(11, 1);
				DPrintf("y: %i ", fruity );
				*/		

				fruit_spr = SpriteManagerAdd( SpriteFruit, fruitx << 3, fruity << 3 );
				return;
			}
		}
	}
}

void spawn_fruit_random()
{
	UINT8 offseti = rand();
	offseti = offseti % 14;

	UINT8 offsetj = rand();
	offsetj = offsetj % 18;

	/*
	DPRINT_POS(11, 0);
	DPrintf("x: %i ", fruitx );
	DPRINT_POS(11, 1);
	DPrintf("y: %i ", fruity );
	*/

	for( UINT8 i = offseti; i != 14; ++i )
	{
		for( UINT8 j = offsetj; j !=  18; ++j )
		{
			if( available_fruits[i][j] )
			{
				fruity = i + 1;
				fruitx = j + 1;
	
				/*			
				DPRINT_POS(11, 0);
				DPrintf("x: %i ", fruitx );
				DPRINT_POS(11, 1);
				DPrintf("y: %i ", fruity );
				*/		

				fruit_spr = SpriteManagerAdd( SpriteFruit, fruitx << 3, fruity << 3 );
				return;
			}
		}

		offsetj = 0;
	}

	spawn_fruit();
}


void update_tail()
{
	UINT8 tx = tail_tilepos[0];
	UINT8 ty = tail_tilepos[1];

	UINT8 nx = 0;
	UINT8 ny = 0;

	UINT8 tail_id = 2;
	UINT8 empty_id = 0;

	UPDATE_TILE( tx, ty, &tail_id, 0 );

	for( UINT8 i = 0; i != tail_len; ++i )
	{
		nx = tailX[i];
		ny = tailY[i];

		tailX[i] = tx;
		tailY[i] = ty;

		tx = nx;
		ty = ny;
	}

	UPDATE_TILE( tx, ty, &empty_id, 0 );
	available_fruits[ty-1][tx-1] = 1;
}

void init_tail()
{
	UINT8 tail_id = 2;

	for( UINT8 i = 0; i != tail_len; ++i )
	{
		UPDATE_TILE( tailX[i], tailY[i], &tail_id, 0 );
	}
}

void Start_SpritePlayer() {

	initarand( DIV_REG );

	tail_len = 0;
	dir_xy[0] = 1;
	dir_xy[1] = 0;
	dir = 8;
	speed_idx = 0;


	SetSpriteAnim(THIS, anim_walk_right, 15);
	move = speed[speed_idx];

	UINT8 tileposX = head_tilepos[0] = THIS->x >> 3;
	UINT8 tileposY = head_tilepos[1] = THIS->y >> 3;

	// init the snake with 3 tails unit
	for( UINT8 i = 0; i != 3; ++i )
	{
		tileposX--;
		tailX[ tail_len ] = tileposX;	
		tailY[ tail_len ] = tileposY;	
		tail_len++;
	}

	tail_end[0] = tailX[ tail_len - 1 ];
	tail_end[1] = tailY[ tail_len - 1 ];	

	init_tail();
	spawn_fruit_random();

	PRINT_POS(6, 0);
	Printf("Score %i", score);

}

UINT8 read_input()
{
	if(KEY_PRESSED(J_UP)) {
		return 1;	
	} 
	if(KEY_PRESSED(J_DOWN)) {
		return 2;
	}
	if(KEY_PRESSED(J_LEFT)) {
		return 4;
	}
	if(KEY_PRESSED(J_RIGHT)) {
		return 8;
	}
	return 0;
}

UINT8 check_vram()
{
	UINT16 vram_offset = 0x9800 + ( head_tilepos[1] << 5 ) + head_tilepos[0];
	return (*(__REG)vram_offset);
}

void Update_SpritePlayer() {

	UINT8 input = read_input();
	UINT8 fruit_eaten = 0;
	UINT8 tail_id = 2;
	UINT8 tile = 0;

	/*
	if( wait )
	{
		tile  = check_vram();
		if( tile != 255 )
		{
			wait = 0;
			if( ( tile != 0 ) || GetScrollTile( head_tilepos[0], head_tilepos[1] ) != 0 )
			{
				SetState(StateLose);
				return;
			}
		}
		else
		{
			return;
		}
	}
	*/

	if( input && dir != input )
	{
		switch( input )
		{
			case 1:
			{
				if( dir != 2 )
				{
					SetSpriteAnim(THIS, anim_walk_up, 15);

					
					dir_xy[0] = 0;
					dir_xy[1] = -1;

					move = 0;
				}
			}
			break;
			case 2:
			{

				if( dir != 1 )
				{
					SetSpriteAnim(THIS, anim_walk_down, 15);

					dir_xy[0] = 0;
					dir_xy[1] = 1;

					move = 0;
				}
			}
			break;
			case 4:
			{

				if( dir != 8 )
				{
					SetSpriteAnim(THIS, anim_walk_left, 15);

					dir_xy[0] = -1;
					dir_xy[1] = 0;


					move = 0;
				}

			}
			break;
			case 8:
			{
				if( dir != 4 )
				{
					SetSpriteAnim(THIS, anim_walk_right, 15);

					dir_xy[0] = 1;
					dir_xy[1] = 0;

					move = 0;
				}

			}
			break;
			default:
			break;
		}
		dir = input;
	}

	if( --move <= 0 )
	{
		PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);

		tail_end[0] = tailX[ tail_len - 1 ];
		tail_end[1] = tailY[ tail_len - 1 ];

		
		/*
		DPRINT_POS(10, 0);
		DPrintf("tx: %i ", tail_end[0] );
		DPRINT_POS(10, 1);
		DPrintf("ty: %i ", tail_end[1] );
		*/


		// move  it
		tail_tilepos[0] = head_tilepos[0];
		tail_tilepos[1] = head_tilepos[1];

		head_tilepos[0] += dir_xy[0];
		head_tilepos[1] += dir_xy[1];

		THIS->x = head_tilepos[0] << 3;
		THIS->y = head_tilepos[1] << 3;

		update_tail();
		tile = check_vram();
		while( tile == 255 )
		{
			tile = check_vram();
		}
		/*
		PRINT_POS(0, 0);
		Printf("vram %u", vram_offset );
		
		PRINT_POS(0, 1);
		Printf("t %u", (UINT16)tile );
		*/	

		if( ( tile != 0 ) || GetScrollTile( head_tilepos[0], head_tilepos[1] ) != 0 )
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xc7, 0xf3, 0x73, 0x86);
			SetState(StateLose);
			/*
			PRINT_POS(2, 2);
			Printf("Dead!");
			*/
			//dead = 1;
		}
		else
		{

			available_fruits[head_tilepos[1]-1][head_tilepos[0]-1] = 0;

			if( head_tilepos[0] == fruitx && head_tilepos[1] == fruity )
			{
				fruit_eaten = 1;
				SpriteManagerRemoveSprite( fruit_spr );
				/*
				PRINT_POS(1, 0);
				Printf("Fruit eaten!");
				*/
				tailX[tail_len] = tail_end[0];
				tailY[tail_len] = tail_end[1];
				
			}

			move = speed[speed_idx];

			if( fruit_eaten )
			{
				//PlayFx(CHANNEL_4, 4, 0x0c, 0x41, 0x30, 0xc0);
				PlayFx(CHANNEL_1, 10, 0x60, 0xc7, 0xf3, 0x73, 0x86);

				available_fruits[ tailY[tail_len] - 1 ] [ tailX[tail_len] - 1  ] = 0;
				UPDATE_TILE( tailX[tail_len], tailY[tail_len], &tail_id, 0 );
				spawn_fruit_random();
				if( ++tail_len >= MAX_TAIL_LEN )
				{
					SetState( StateWin );
					return;
				}

				if( ++speed_idx > MAX_SPEED_IDX )
				{
					speed_idx = MAX_SPEED_IDX;
				}
				score++;
				PRINT_POS(6, 0);
				Printf("Score %i", score);

			}
			else
			{
				/*
				PRINT_POS(1, 0);
				Printf("       ");
				*/
			}
		}
	}
}




void Destroy_SpritePlayer() {
}
