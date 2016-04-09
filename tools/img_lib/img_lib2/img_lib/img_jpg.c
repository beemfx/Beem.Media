#include <setjmp.h>
#include "img_private.h"
#include "jpeg-6b\jinclude.h"
#include "jpeg-6b\jpeglib.h"

/* The exception handling code, see also
	jerror.h. */
jmp_buf g_mark;
void img_error_exit (j_common_ptr cinfo)
{
  /* Let the memory manager delete any temp files before we die */
  jpeg_destroy(cinfo);
  /* Do a long jump back to the caller and send the exit code.*/
  longjmp(g_mark, 1);
  //exit(0);
}

 HIMG IMG_LoadJPGCallbacks(img_void* stream, IMG_CALLBACKS* lpCB)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	IMAGE_S* pImage=IMG_NULL;
	img_dword i=0;
	unsigned char* buf=IMG_NULL;

	//Seek to the beginning of the file.
	lpCB->seek(stream, 0, IMG_SEEK_SET);
	
	/* Exception handling code, if set jump
		is not 0 it means that the jpeg6b library
		failed.*/
	if(setjmp(g_mark))
	{
		if(pImage)
		{
			if(pImage->pImage)
				free(pImage);
				
			if(buf)
				free(buf);
				
			free(pImage);
		}
		
		return IMG_NULL;
	}
	
	
	pImage=(IMAGE_S*)malloc(sizeof(IMAGE_S));
	if(!pImage)
	{
		return IMG_NULL;
	}
	/* Make sure we zero out the structure,
		that way if jpeg6b fails we
		won't try to deallocate memory that hasn't
		been allocated.*/
	memset(pImage, 0, sizeof(IMAGE_S));
		
	//try...
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	
	jpeg_stdio_src(&cinfo, stream, lpCB->read);
	jpeg_read_header(&cinfo, TRUE);

	
	memset(pImage, 0, sizeof(IMAGE_S));
	pImage->nBitDepth=24;
	pImage->nDataFmt=IMGFMT_B8G8R8; //The RGB image format for JPEGS is backwards it is B8G8R8 in the img_lib format.
	pImage->nWidth=cinfo.image_width;
	pImage->nHeight=cinfo.image_height;
	pImage->nDataSize=pImage->nWidth*pImage->nHeight*3;
	pImage->nOrient=IMGORIENT_TOPLEFT;
	pImage->pImage=malloc(pImage->nDataSize);
	
	if(!pImage->pImage)
	{
		free(pImage);
		jpeg_abort_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		return IMG_NULL;
	}
	
	cinfo.out_color_space=JCS_RGB;
	jpeg_start_decompress(&cinfo);
	
	//We can simply read the scanlines into the last scanline of the img_lib file
	//that way we don't need a temporary buffer to read scanlines.
	buf=(img_byte*)pImage->pImage+pImage->nWidth*(pImage->nHeight-1)*3;	
	for(i=0; jpeg_read_scanlines(&cinfo, &buf, 1); i++)
	{
		memcpy((img_byte*)pImage->pImage+i*pImage->nWidth*3, buf, pImage->nWidth*3);
	}
	
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	//ending try block... (goes to setjmp if it fails).
	return pImage;
}