#ifndef _P5IMAGE_H_
#define _P5IMAGE_H_ 1

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#ifdef _WIN32
  #define GL_CLAMP_TO_EDGE 0x812F
#endif

TexImage *img_new() {
  TexImage *m;
  m = malloc(sizeof(TexImage));
  return m;
}

int p5_imageMode(int mode) {
	ctx->imageMode = mode;
}

void p5_loadImage(char* filename,int imgId,Context *ctx) {
	if ((imgId<0)||(imgId>100)||(ctx->imageTable[imgId]!=NULL)) return;
	int width;
	int height;
    
	ctx->imageTable[imgId] = img_new();
	GLuint tex_ID;
	
	glEnable(GL_TEXTURE_2D);
	//glGenTextures(1, &ctx->imageTable[imgId]->texobj);
	//glBindTexture(GL_TEXTURE_2D,ctx->imageTable[imgId]->texobj);
	
	glGenTextures(1, &tex_ID);
	glBindTexture(GL_TEXTURE_2D,tex_ID);
	
	ctx->imageTable[imgId]->texobj = tex_ID;

    int x,y,n;
    unsigned char *image = stbi_load(filename, &width, &height, &n, STBI_rgb_alpha);
	ctx->imageTable[imgId]->tex_width = width;
	ctx->imageTable[imgId]->tex_height = height;
	if (NULL == image) {
		printf( "Image loading error %s\n",stbi_failure_reason());
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	stbi_image_free(image);
}

void p5_imageResize(int imgId,float a, float b, float c, float d) {
	switch (ctx->imageMode) {
	case P5_CENTER:
	    a = a-(c/2);
		b = b-(d/2);
    	break;
	case P5_CORNERS:
	    c = c-a;
		d = d-b;
	   	break;
	}
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ctx->imageTable[imgId]->texobj);
	//glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glColor3ub(255,255,255);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glTranslatef(a+c/2,b+d/2,0);
	glScalef(c/2,d/2,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void p5_image(int imgId,float a, float b) {
	p5_imageResize(imgId,a,b,ctx->imageTable[imgId]->tex_width,ctx->imageTable[imgId]->tex_height);
}
#endif