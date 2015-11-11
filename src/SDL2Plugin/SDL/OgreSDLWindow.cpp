/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "../OgreSDLWindow.h"
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreImageCodec.h>
#include <OGRE/OgreException.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreStringConverter.h>
#include "../OgreGLPixelFormat.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#   include <windows.h>
#   include <wingdi.h>
#   include <GL/gl.h>
#   define GL_GLEXT_PROTOTYPES
//#   include "glprocs.h"
#   include <GL/glu.h>
#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
#   include <GL/gl.h>
#   include <GL/glu.h>
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#   include <OpenGL/gl.h>
#   define GL_EXT_texture_env_combine 1
#   include <OpenGL/glext.h>
#   include <OpenGL/glu.h>
#endif

#include <OpenBlox.h>

namespace Ogre {
    SDLWindow::SDLWindow() : mScreen(NULL), mActive(false), mClosed(false), mVSync(false){}

    SDLWindow::~SDLWindow(){}

	void SDLWindow::create(const String& name, unsigned int width, unsigned int height, bool fullScreen, const NameValuePairList *miscParams){
		mScreen = SDL_GL_GetCurrentWindow();

        mName = name;

        mWidth = width;
        mHeight = height;

        mActive = true;

        //glXGetVideoSyncSGI = (int (*)(unsigned int *))SDL_GL_GetProcAddress("glXGetVideoSyncSGI");
        //glXWaitVideoSyncSGI = (int (*)(int, int, unsigned int *))SDL_GL_GetProcAddress("glXWaitVideoSyncSGI");
    }

    void SDLWindow::destroy(){
        mScreen = NULL;
        mActive = false;

        Root::getSingleton().getRenderSystem()->detachRenderTarget(this->getName());
    }

    bool SDLWindow::isActive() const{
        return mActive;
    }

    bool SDLWindow::isClosed() const{
        return mClosed;
    }

    void SDLWindow::reposition(int left, int top){
    	SDL_SetWindowPosition(mScreen, left, top);
    }

    void SDLWindow::resize(unsigned int width, unsigned int height){
    	SDL_SetWindowSize(mScreen, width, height);

        mWidth = width;
        mHeight = height;

        for(ViewportList::iterator it = mViewportList.begin(); it != mViewportList.end(); ++it){
            (*it).second->_updateDimensions();
        }
    }

    void SDLWindow::_resized(unsigned int width, unsigned int height){
    	mWidth = width;
		mHeight = height;

		for(ViewportList::iterator it = mViewportList.begin(); it != mViewportList.end(); ++it){
			(*it).second->_updateDimensions();
		}
	}

    void SDLWindow::setVSyncEnabled(bool vsync){
        mVSync = vsync;
	}

	bool SDLWindow::isVSyncEnabled() const{
        return mVSync;
	}

    void SDLWindow::swapBuffers(){}

	void SDLWindow::copyContentsToMemory(const PixelBox &dst, FrameBuffer buffer){
		if ((dst.left < 0) || (dst.right > mWidth) ||
			(dst.top < 0) || (dst.bottom > mHeight) ||
			(dst.front != 0) || (dst.back != 1))
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
						"Invalid box.",
						"SDLWindow::copyContentsToMemory" );
		}
	
		if(buffer == FB_AUTO){
			buffer = mIsFullScreen? FB_FRONT : FB_BACK;
		}
	
		GLenum format = Ogre::GLPixelUtil::getGLOriginFormat(dst.format);
		GLenum type = Ogre::GLPixelUtil::getGLOriginDataType(dst.format);
	
		if((format == GL_NONE) || (type == 0)){
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
				"Unsupported format.",
				"SDLWindow::copyContentsToMemory" );
		}
	
		// Switch context if different from current one
		RenderSystem* rsys = Root::getSingleton().getRenderSystem();
		rsys->_setViewport(this->getViewport(0));
	
        if(dst.getWidth() != dst.rowPitch)
            glPixelStorei(GL_PACK_ROW_LENGTH, dst.rowPitch);
		// Must change the packing to ensure no overruns!
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
	
		glReadBuffer((buffer == FB_FRONT)? GL_FRONT : GL_BACK);
        glReadPixels((GLint)0, (GLint)(mHeight - dst.getHeight()),
                     (GLsizei)dst.getWidth(), (GLsizei)dst.getHeight(),
                     format, type, dst.getTopLeftFrontPixelPtr());
	
		// restore default alignment
		glPixelStorei(GL_PACK_ALIGNMENT, 4);
        glPixelStorei(GL_PACK_ROW_LENGTH, 0);
        
        PixelUtil::bulkPixelVerticalFlip(dst);
	}
}
