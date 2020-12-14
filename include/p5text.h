#ifndef _P5TEXT_H_
#define _P5TEXT_H_ 1

#if _WIN32
#include <Windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

void p5_loadFont(char *fontname,int fontId,Context *ctx) {
	if (ctx->fontTable[fontId]!=NULL)
	  return;
	ctx->fontId = fontId;
	ctx->fontTable[fontId] = txfLoadFont(fontname);
    if (ctx->fontTable[fontId] == NULL) {
     fprintf(stderr, "Problem loading %s, %s\n",
       fontname, txfErrorString());
	   return;
    }
	glEnable(GL_TEXTURE_2D);
	//glAlphaFunc(GL_GEQUAL, 0.0625);
	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	
	//glActiveTexture(GL_TEXTURE0+ctx->fontId);
	txfEstablishTexture(ctx->fontTable[fontId], 0, GL_TRUE);
	
	glDisable(GL_TEXTURE_2D);

}

void p5_textFont(int fontId) {
	ctx->textRatio = 1.0f;
	ctx->fontId = fontId;
}

void p5_textAlign(int align) {
	ctx->textAlign = align;
}

int p5_charWidth(char c) {
	return 0;
}

int p5_textWidth(char * text) {
  if (ctx->fontId==-1)
	p5_loadFont("default.txf",0,ctx);
  int width, ascent, descent;
  txfGetStringMetrics(ctx->fontTable[ctx->fontId], text, strlen(text),
        &width, &ascent, &descent);
  return width;
}

void p5_textSize(float textSize) {
  if (ctx->fontId==-1)
	p5_loadFont("default.txf",0,ctx);
  int width, ascent, descent;
  txfGetStringMetrics(ctx->fontTable[ctx->fontId], "X", 1,
      &width, &ascent, &descent);
  ctx->textRatio = textSize/(ascent+descent);
}

void p5_text(char * text, float x, float y) {
	
   if (ctx->fontId==-1)
	 p5_loadFont("default.txf",0,ctx);    
	
	int textWidth = p5_textWidth(text);  
	
    switch (ctx->textAlign) {
  	  case P5_CENTER:
  	    x -= textWidth/2*ctx->textRatio;
  	    break;
  	  case P5_RIGHT:
  	    x -= textWidth*ctx->textRatio;
  	    break;
  	  case P5_LEFT:
  	    break;
    }
	
	glColor4f(ctx->fill->red,ctx->fill->green,ctx->fill->blue,ctx->fill->alpha);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(ctx->textRatio,-ctx->textRatio,1.0f);
	
	glEnable(GL_TEXTURE_2D);
	
	txfBindFontTexture(ctx->fontTable[ctx->fontId]);
	
	txfRenderString(ctx->fontTable[ctx->fontId],text,strlen(text));

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

#endif