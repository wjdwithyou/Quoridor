#include "dxfunc.h"

IDirect3DDevice9* Device;
ID3DXSprite* Sprite;
ID3DXFont* Font = NULL;

D3DXCOLOR Color; 
D3DXMATRIX World;
D3DXMATRIX Translation;
D3DXMATRIX Rotation;
D3DXMATRIX Scaling;

void InitializeDevice() {
	HRESULT hr;
	IDirect3D9* d3d9;
	
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DCAPS9 caps;

	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)? D3DCREATE_HARDWARE_VERTEXPROCESSING: D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS PresentParameters; 
	
	PresentParameters.BackBufferWidth = WindowWidth;
	PresentParameters.BackBufferHeight = WindowHeight;
	PresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	PresentParameters.BackBufferCount = 1;
	PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	PresentParameters.MultiSampleQuality = 0;
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParameters.hDeviceWindow = hWnd;
	PresentParameters.Windowed = true;
	PresentParameters.EnableAutoDepthStencil = true;
	PresentParameters.Flags = 0;
	PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	
	hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &PresentParameters, &Device);
	
	if (FAILED(hr)) {
		PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &PresentParameters, &Device);

		if (FAILED(hr)) {
			d3d9->Release();

			MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			
			return;
		}
	}
	
	d3d9->Release();

	D3DXCreateSprite(Device, &Sprite);

	D3DXFONT_DESC fontDesc;

	ZeroMemory(&fontDesc, sizeof(fontDesc));

	fontDesc.Height = 20;
	fontDesc.Width = 10;
	fontDesc.Weight = 1000;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;

	strcpy_s(fontDesc.FaceName, "바탕");

	D3DXCreateFontIndirect(Device, &fontDesc, &Font); //폰트를 만든다.
	//첫번째 인수는 다이렉트의 디바이스, 두번째는 폰트의 정보를 담은 구조체, 세번째는 리턴될 폰트인터페이스

	D3DXMatrixIdentity(&World);
	D3DXMatrixTranslation(&Translation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationZ(&Rotation, 0.0f); 
	D3DXMatrixScaling(&Scaling, 1.0f, 1.0f, 1.0f);
	Color = D3DCOLOR_RGBA(255, 255, 255, 255);
}

void LoadTexture(char* TextureFileName, IDirect3DTexture9** texture_) {
	D3DXIMAGE_INFO ImageInfo;
	D3DXGetImageInfoFromFile(TextureFileName, &ImageInfo);
	D3DXCreateTextureFromFileEx(Device, TextureFileName, ImageInfo.Width, ImageInfo.Height, 1, D3DUSAGE_AUTOGENMIPMAP, ImageInfo.Format, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, texture_);

	return;
}

void DrawTexture(IDirect3DTexture9* texture_, float x, float y, float size, float angle) {
	// 좌상단 기준
	D3DXMatrixIdentity(&World);	
	D3DXMatrixTranslation(&Translation, x, y, 0.0f);
	D3DXMatrixRotationZ(&Rotation, angle);
	D3DXMatrixScaling(&Scaling, size, size, 1.0f);

	D3DXMatrixMultiply(&Scaling, &Scaling, &Rotation);
	D3DXMatrixMultiply(&World, &Scaling, &Translation);
	Sprite -> SetTransform(&World);

	Color = D3DCOLOR_RGBA(255, 255, 255, 255);

	Sprite -> Draw(texture_, NULL, NULL, NULL, Color);

	return;
}

void DrawTexture(IDirect3DTexture9* texture_, Location loc, float size, float angle){
	D3DXMatrixIdentity(&World);	
	D3DXMatrixTranslation(&Translation, static_cast<float>(loc.x), static_cast<float>(loc.y), 0.0f);
	D3DXMatrixRotationZ(&Rotation, angle);
	D3DXMatrixScaling(&Scaling, size, size, 1.0f);

	D3DXMatrixMultiply(&Scaling, &Scaling, &Rotation);
	D3DXMatrixMultiply(&World, &Scaling, &Translation);
	Sprite -> SetTransform(&World);

	Color = D3DCOLOR_RGBA(255, 255, 255, 255);

	Sprite -> Draw(texture_, NULL, NULL, NULL, Color);

	return;
}

void DrawC(IDirect3DTexture9* texture_, float x, float y, float size, float angle, float c) {
	// 센터 기준
	// 임시. 수정 및 보완 필요
	D3DXMatrixIdentity(&World);
	D3DXMatrixTranslation(&Translation, x, y, 0.0f);
	D3DXMatrixRotationZ(&Rotation, angle);
	D3DXMatrixScaling(&Scaling, size, size, 1.0f);

	D3DXMatrixMultiply(&Scaling, &Scaling, &Rotation);
	D3DXMatrixMultiply(&World, &Scaling, &Translation);
	Sprite -> SetTransform(&World);

	Color = D3DCOLOR_RGBA(255, 255, 255, 255);

	D3DXVECTOR3 center(c, c, 0);
	Sprite -> Draw(texture_, NULL, &center, NULL, Color);

	return;
}
/*
void DrawEnding(IDirect3DTexture9* texture_, float x, float y, float size, float angle) {
	// for overlap
	D3DXMatrixIdentity(&World);	
	D3DXMatrixTranslation(&Translation, x, y, 0.0f);
	D3DXMatrixRotationZ(&Rotation, angle);
	D3DXMatrixScaling(&Scaling, size, size, 1.0f);

	D3DXMatrixMultiply(&Scaling, &Scaling, &Rotation);
	D3DXMatrixMultiply(&World, &Scaling, &Translation);
	Sprite -> SetTransform(&World);

	Color = D3DCOLOR_RGBA(255, 255, 255, ending);

	Sprite -> Draw(texture_, NULL, NULL, NULL, Color);

	return;
}
*/

void ReleaseDevice() {
	if (Sprite != NULL){
		Sprite->Release();
		Sprite = NULL;
	}
	if (Device != NULL){
		Device->Release();
		Device = NULL;
	}
	if (Font != NULL){
		Font->Release();
		Font = NULL;
	}
}