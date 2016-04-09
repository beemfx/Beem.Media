#include <setjmp.h>
#include <malloc.h>
#include "libpng-1.2.16\png.h"
#include "img_private.h"

typedef struct _png_io
{
	img_void* file;
	IMG_CALLBACKS* pCB;
}png_io, *png_io_ptr;

void user_error_fn(png_structp png_ptr, png_const_charp error_msg)
{
	//OutputDebugStringA(error_msg);
	//OutputDebugStringA("\n");
}
void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
	//We don't care...
}


void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_io_ptr pio=png_get_io_ptr(png_ptr);
	if(!pio)
		return;
	pio->pCB->read((img_void*)data, 1, (img_uint)length, pio->file);
}


HIMG IMG_LoadPNGCallbacks(img_void* stream, IMG_CALLBACKS* lpCB)
{
	png_structp png_ptr=IMG_NULL;
	png_infop info_ptr=IMG_NULL;
	png_infop end_info=IMG_NULL;
	png_io io_ptr={IMG_NULL, IMG_NULL};
	
	img_dword i=0;
	//The img_lib stuff;
	IMAGE_S* pImage=IMG_NULL;


	lpCB->seek(stream, 0, IMG_SEEK_SET);
	//Create the png_struct.
	png_ptr = png_create_read_struct(
		PNG_LIBPNG_VER_STRING, 
		IMG_NULL,//(png_voidp)user_error_ptr,
		user_error_fn, 
		user_warning_fn);
		
	if (!png_ptr)
		return IMG_NULL;
		
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(
			&png_ptr,
			(png_infopp)NULL, 
			(png_infopp)NULL);
			
		IMG_SAFE_FREE(pImage);
		return IMG_NULL;
	}
	//If the png reading functions fail at
	//some point we have this error catching.
	
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(
			&png_ptr,
			&info_ptr,
			&end_info);
		//If the image has been allocated, we'll free any memory.
		if(pImage)
		{
			IMG_SAFE_FREE(pImage->pImage);
			IMG_SAFE_FREE(pImage);
		}
		return IMG_NULL;	
	}
	
	
	io_ptr.file=stream;
	io_ptr.pCB=lpCB;
	//Set up the reading callbacks...
	png_set_read_fn(png_ptr, &io_ptr, user_read_data);
	//png_set_read_user_chunk_fn(png_ptr, &io_ptr, user_read_data);
	//png_set_sig_bytes(png_ptr, 0);
	
	//Get the image dimensions:
	
	//Start reading the image:
	//png_read_info(png_ptr, info_ptr);
	//We won't support 64 bit images and we'll revers the color components.
	//We also make sure we don't get a paletted image.
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16|PNG_TRANSFORM_BGR|PNG_TRANSFORM_EXPAND, png_voidp_NULL);
	
	
	
	//Allocate memory for the image:	
	pImage=malloc(sizeof(IMAGE_S));
	if(!pImage)
		longjmp(png_jmpbuf(png_ptr), 1);
	memset(pImage, 0, sizeof(IMAGE_S));	
	pImage->nWidth=(img_word)png_get_image_width(png_ptr, info_ptr);
	pImage->nHeight=(img_word)png_get_image_height(png_ptr, info_ptr);
	pImage->nBitDepth=(img_byte)png_get_bit_depth(png_ptr, info_ptr)*png_get_channels(png_ptr, info_ptr);
	pImage->nDataFmt=pImage->nBitDepth==32?IMGFMT_A8R8G8B8:IMGFMT_R8G8B8;
	pImage->nDataSize=pImage->nWidth*pImage->nHeight*pImage->nBitDepth/8;
	pImage->nOrient=IMGORIENT_TOPLEFT;
	pImage->pImage=malloc(pImage->nDataSize);
	if(!pImage->pImage)
		longjmp(png_jmpbuf(png_ptr), 1);
	
	{
	png_bytepp row_pointers=png_get_rows(png_ptr, info_ptr);
	img_dword row_length=pImage->nWidth*pImage->nBitDepth/8;
	for(i=0; i<pImage->nHeight; i++)
	{
		memcpy((img_byte*)pImage->pImage+i*row_length, row_pointers[i], row_length);
	}
	
	}
	
	png_destroy_read_struct(
		&png_ptr,
		&info_ptr,
		&end_info);
	return pImage;	
}