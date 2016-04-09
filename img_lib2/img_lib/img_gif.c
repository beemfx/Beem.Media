#include <memory.h>
#include <malloc.h>
#include "img_private.h"
#include "ungif-4x\gif_lib.h"

int DGifSlurp(GifFileType * GifFile);

IMG_CALLBACKS* g_pCB=NULL;

int __cdecl ReadGif(GifFileType * pGifFile, GifByteType * pBuffer, int nSize)
{
	return g_pCB->read(pBuffer, 1, nSize, pGifFile->UserData);	
}


HIMG IMG_LoadGIFCallbacks(img_void* stream, IMG_CALLBACKS* lpCB)
{
	IMAGE_S* pImage=IMG_NULL;
	GifFileType* pGifFile=IMG_NULL;
	ColorMapObject* pCM=IMG_NULL;
	
	g_pCB=lpCB;
	//Seek to the beginning of the file.
	lpCB->seek(stream, 0, IMG_SEEK_SET);
	pGifFile=DGifOpen(stream, ReadGif);
	if(!pGifFile)
	{
		return IMG_NULL;
	}
		
	//We have a valid GIF, lets decode it.
	
	if(DGifSlurp(pGifFile)!=GIF_OK)
	{
		DGifCloseFile(pGifFile);
		return IMG_NULL;
	}
	pImage=malloc(sizeof(IMAGE_S));
	if(!pImage)
	{
		DGifCloseFile(pGifFile);
		return IMG_NULL;
	}
	
	pCM=pGifFile->SavedImages[0].ImageDesc.ColorMap?pGifFile->SavedImages[0].ImageDesc.ColorMap:pGifFile->SColorMap;
	memset(pImage, 0, sizeof(IMAGE_S));
	pImage->nWidth=pGifFile->SavedImages[0].ImageDesc.Width;//pGifFile->Image.Width;
	pImage->nHeight=pGifFile->SavedImages[0].ImageDesc.Height;
	pImage->nBitDepth=8;
	pImage->nDataFmt=IMGFMT_PALETTE;
	pImage->nOrient=IMGORIENT_TOPLEFT;
	pImage->nPaletteBitDepth=24;
	pImage->nPaletteFmt=IMGFMT_B8G8R8;
	pImage->nPaletteEntries=pCM->ColorCount;
	pImage->nPaletteSize=pImage->nPaletteEntries*pImage->nPaletteBitDepth/8;
	pImage->nDataSize=pImage->nWidth*pImage->nHeight*pImage->nBitDepth/8;
	pImage->pImage=malloc(pImage->nDataSize);
	pImage->pPalette=malloc(pImage->nPaletteSize);
	
	if(!pImage->pImage || !pImage->pPalette)
	{
		IMG_SAFE_FREE(pImage->pImage);
		IMG_SAFE_FREE(pImage->pPalette);
		
		IMG_SAFE_FREE(pImage);
		DGifCloseFile(pGifFile);
		return IMG_NULL;
	}
	
	memcpy(pImage->pPalette, pCM->Colors, pImage->nPaletteSize);
	if(!pGifFile->SavedImages[0].ImageDesc.Interlace)
	{
		memcpy(pImage->pImage, pGifFile->SavedImages[0].RasterBits, pImage->nDataSize);
	}
	else
	{
		//De-Interlace.
		img_dword i=0, j=0;
		img_byte* pSrcBits=(img_byte*)pGifFile->SavedImages[0].RasterBits;
		img_byte* pDestBits=(img_byte*)pImage->pImage;
		
		
		for(i=0,j=0; i<pImage->nHeight; i+=8,j++)
		{
			memcpy(pDestBits+i*pImage->nWidth, pSrcBits+j*pImage->nWidth, pImage->nWidth*pImage->nBitDepth/8);
		}
		for(i=4; i<pImage->nHeight; i+=8, j++)
		{
			memcpy(pDestBits+i*pImage->nWidth, pSrcBits+j*pImage->nWidth, pImage->nWidth*pImage->nBitDepth/8);
		}
		for(i=2; i<pImage->nHeight; i+=4, j++)
		{
			memcpy(pDestBits+i*pImage->nWidth, pSrcBits+j*pImage->nWidth, pImage->nWidth*pImage->nBitDepth/8);
		}
		for(i=1; i<pImage->nHeight; i+=2, j++)
		{
			memcpy(pDestBits+i*pImage->nWidth, pSrcBits+j*pImage->nWidth, pImage->nWidth*pImage->nBitDepth/8);
		}
		
	}

	
	DGifCloseFile(pGifFile);
	return pImage;
}

int DGifSlurp(GifFileType * GifFile) 
{

    int ImageSize;
    GifRecordType RecordType;
    SavedImage *sp;
    GifByteType *ExtData;
    SavedImage temp_save;

    temp_save.ExtensionBlocks = NULL;
    temp_save.ExtensionBlockCount = 0;

    do {
        if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR)
            return (GIF_ERROR);

        switch (RecordType) {
          case IMAGE_DESC_RECORD_TYPE:
              if (DGifGetImageDesc(GifFile) == GIF_ERROR)
                  return (GIF_ERROR);

              sp = &GifFile->SavedImages[GifFile->ImageCount - 1];
              ImageSize = sp->ImageDesc.Width * sp->ImageDesc.Height;

              sp->RasterBits = (unsigned char *)malloc(ImageSize *
                                                       sizeof(GifPixelType));
              if (sp->RasterBits == NULL) {
                  return GIF_ERROR;
              }
              if (DGifGetLine(GifFile, sp->RasterBits, ImageSize) ==
                  GIF_ERROR)
                  return (GIF_ERROR);
              if (temp_save.ExtensionBlocks) {
                  sp->ExtensionBlocks = temp_save.ExtensionBlocks;
                  sp->ExtensionBlockCount = temp_save.ExtensionBlockCount;

                  temp_save.ExtensionBlocks = NULL;
                  temp_save.ExtensionBlockCount = 0;

                  /* FIXME: The following is wrong.  It is left in only for
                   * backwards compatibility.  Someday it should go away. Use 
                   * the sp->ExtensionBlocks->Function variable instead. */
                  sp->Function = sp->ExtensionBlocks[0].Function;
              }
              break;

          case EXTENSION_RECORD_TYPE:
              if (DGifGetExtension(GifFile, &temp_save.Function, &ExtData) ==
                  GIF_ERROR)
                  return (GIF_ERROR);
              while (ExtData != NULL) {

                  /* Create an extension block with our data */
                  if (AddExtensionBlock(&temp_save, ExtData[0], &ExtData[1])
                      == GIF_ERROR)
                      return (GIF_ERROR);

                  if (DGifGetExtensionNext(GifFile, &ExtData) == GIF_ERROR)
                      return (GIF_ERROR);
                  temp_save.Function = 0;
              }
              break;

          case TERMINATE_RECORD_TYPE:
              break;

          default:    /* Should be trapped by DGifGetRecordType */
              break;
        }
    } while (RecordType != TERMINATE_RECORD_TYPE);

    /* Just in case the Gif has an extension block without an associated
     * image... (Should we save this into a savefile structure with no image
     * instead? Have to check if the present writing code can handle that as
     * well.... */
    if (temp_save.ExtensionBlocks)
        FreeExtension(&temp_save);

    return (GIF_OK);
}