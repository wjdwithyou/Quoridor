#include "image.h"

IDirect3DTexture9* Background_Texture;
IDirect3DTexture9* Board_Texture;
IDirect3DTexture9* Character_Black_Texture;
IDirect3DTexture9* Character_Brown_Texture;

void ReleaseTexture(){
	if (Background_Texture != NULL) {
		Background_Texture->Release();
		Background_Texture = NULL;
	}
	if (Board_Texture != NULL){
		Board_Texture->Release();
		Board_Texture = NULL;
	}
	if (Character_Black_Texture != NULL){
		Character_Black_Texture->Release();
		Character_Black_Texture = NULL;
	}
	if (Character_Brown_Texture != NULL){
		Character_Brown_Texture->Release();
		Character_Brown_Texture = NULL;
	}
}