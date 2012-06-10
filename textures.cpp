
bool createRenderingContext(HWND hWnd, int w, int h)
{
	PIXELFORMATDESCRIPTOR pfd;	
	int pixelFormat;
	int iPixelType; 
	u32 dwFlags;
	memset( &pfd, 0, sizeof(PIXELFORMATDESCRIPTOR) ) ;
	iPixelType = PFD_TYPE_RGBA;
	dwFlags  = PFD_SUPPORT_OPENGL |  
             PFD_DOUBLEBUFFER |    
             PFD_DRAW_TO_WINDOW;   
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); 
	pfd.nVersion = 1 ;                          
	pfd.dwFlags =  dwFlags ;
	pfd.iPixelType = iPixelType ;
	pfd.cColorBits = 32 ;
	pfd.cDepthBits = 24;                       
	pfd.cStencilBits = 8;                      
	pfd.iLayerType = PFD_MAIN_PLANE ;          
	m_hWnd = hWnd;
	m_width = w;
	m_height = h;

	if (!(m_dc = GetDC(m_hWnd)))			
		return false;
			
	if (!(pixelFormat=ChoosePixelFormat(m_dc, &pfd)))
		return false;
			
	if (!SetPixelFormat(m_dc, pixelFormat, &pfd))	
		return false;
			
	if (!(m_rc = wglCreateContext(m_dc)))			
		return false;
			
	if (!wglMakeCurrent(m_dc, m_rc))				
		return false;

	return true;
}