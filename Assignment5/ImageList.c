/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

static IENTRY *NewImageEntry(IMAGE *image)
{
	IENTRY *e;
	e = (IENTRY *)malloc(sizeof(IENTRY));
	if (! e)
	{
		return NULL;
	}
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->image = image;
	return e;
}

static IMAGE *DeleteImageEntry(IENTRY *e)
{
	IMAGE *image;
	assert(e);
	image = e->image;
	free(e);
	return image;
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
        ILIST *list;
        list = (ILIST *)malloc(sizeof(ILIST));
        assert(list);
        if(!list) {
                return NULL;
        }
        list->Length = 0;
        list->First = NULL;
        list->Last = NULL;
        return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
        IENTRY *e;
        IENTRY *n;
        IMAGE *image;
        assert(list);
        e = list->First;
        while(e) {
                n = e->Next;
                image = DeleteImageEntry(e);
                if(image) {
                        DeleteImage(image);
                }
                e = n;
        }
        free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
        IENTRY *entry;
        assert(list);
        assert(RGBimage);

        entry = NewImageEntry(RGBimage);
        entry->List = list;
        entry->Next = NULL;

        if(list->Length == 0) {
                entry->Prev = NULL;
                list->First = entry;
                list->Last = entry;
        }
        else {
                entry->Prev = list->Last;
                list->Last->Next = entry;
                list->Last = entry;
        }
        entry->image = RGBimage;
        list->Length++;
        
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{
        IENTRY *entry;
        assert(list);
        assert(YUVimage);

        entry = NewImageEntry(YUVimage);
        entry->List = list;
        entry->Next = NULL;

        if(list->Length == 0) {
                entry->Prev = NULL;
                list->First = entry;
                list->Last = entry;
        }
        else {
                entry->Prev = list->Last;
                list->Last->Next = entry;
                list->Last = entry;
        }
        entry->image = YUVimage;
        list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
        int i;
        int length;

        for (i = 0; i < start; i++) {
                IENTRY *temp = NULL;
                assert(list);
                if (list->First;) {
                        temp = list->First;
                        list->First = temp->Next;
                        if (list->First) {
                                list->First->Prev = NULL;
                        }
                        else 
                        {
                                assert(list->Last == temp);
                                list->Last = NULL;
                        }
                        list->Length--;
                        DeleteImage(temp->image);
                        DeleteImageEntry(temp);

                }
        }
        for (i = 0; i < (length - end); i++) {
                IENTRY *temp = NULL;
                assert(list);
                if (list->Last) {
                        temp = list->Last;
                        list->Last = temp->Prev;
                        if (list->Last) {
                                list->Last->Next = NULL;
                        }
                        else 
                        {
                                assert(list->First == temp);
                                list->First = NULL;
                        }
                        list->Length--;
                        DeleteImage(temp->image);
                        DeleteImageEntry(temp);
                }
        }
}

/* Fast forward an image list */
unsigned int FastImageList(ILIST *list, unsigned int factor)
{
        int i;
        int j;
        int k;
        int length;
        int num;
        length = list->Length;
        num = length / factor;
        
        for(i = 0; i < num; i++) {
                list->First = list->First->Next;

                for(j = 0; j < (factor - 1); j++) {
                        IENTRY *temp = NULL;
                        assert(list);
                        if (list->Last) {
                                temp = list->First;
                                list->First = temp->Next;
                                if (list->First) {
                                        list->First->Prev = temp->Prev;
                                        temp->Prev->Next = list->First;
                                }
                                else 
                                {
                                        assert(list->Last == temp);
                                        list->Last = temp->Prev;
                                        temp->Prev->Next = NULL;
                                        list->First = list->Last;
                                }
                                list->Length--;
                                DeleteImage(temp->image);
                                DeleteImageEntry(temp);
                        }
                }
        }
        num = length/factor;
        if (length % factor != 0) {
                num++;
        }
                for(k = 0; k < (length - num * factor); k++) {
                      list->First = list->Last->Prev;
                }
                return num;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
        IENTRY *Current, *Next, *Prev;
        assert(list);
        Current = list->First;
        Next = list->First->Next;
        Prev = list->First->Prev;

        while(1) {
                Current->Next = Prev;
                Current->Prev = Next;
                Current = Next;
                if(Next == NULL) {
                        break;
                }
                Prev = Current;
                Next = Next->Next;
                Current = Next;
        }
        list->First = Current;
        list->Last = list->First;
}

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
        IENTRY *entry;
        assert(list);
        assert(RGBimage);

        entry = NewImageEntry(RGBimage);
        entry->List = list;
        entry->Prev = NULL;

        if(list->Length == 0) {
                entry->Next = NULL;
                list->First = entry;
                list->Last = entry;
        }
        else {
                entry->Next = list->First;
                list->First->Prev = entry;
                list->First = entry;
        }
        entry->image = RGBimage;
        list->Length++;
}
