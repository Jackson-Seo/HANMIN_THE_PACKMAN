癤�#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS�뒗 誘몃━ 蹂닿린, 異뺤냼�뙋 洹몃┝ 諛� 寃��깋 �븘�꽣 泥섎━湲곕�� 援ы쁽�븯�뒗 ATL �봽濡쒖젥�듃�뿉�꽌 �젙�쓽�븷 �닔 �엳�쑝硫�
// �빐�떦 �봽濡쒖젥�듃��� 臾몄꽌 肄붾뱶瑜� 怨듭쑀�븯�룄濡� �빐 以띾땲�떎.
#ifndef SHARED_HANDLERS
#include "OpenGLProject.h"
#endif

#include "OpenGLProjectDoc.h"
#include "OpenGLProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(COpenGLProjectView, CView)
BEGIN_MESSAGE_MAP(COpenGLProjectView, CView)
	// �몴以� �씤�뇙 紐낅졊�엯�땲�떎.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	// �쑀���媛� 異붽���븳 硫붿떆吏� �엯�땲�떎
	ON_MESSAGE(UWM_CUSTOM1, &COpenGLProjectView::OnUwmCustom1)
	ON_MESSAGE(UWM_CHECKED, &COpenGLProjectView::OnUwmChecked)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

bool COpenGLProjectView::SetDevicePixelFormat(HDC hdc) {
	int pixelformat;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER |
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		8,
		0,
		8,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("ChoosePixelFormat Failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
		MessageBox(LPCTSTR("SetPixelFormat Failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}
	return TRUE;
}

// COpenGLProjectView �깮�꽦/�냼硫�
COpenGLProjectView::COpenGLProjectView() noexcept { }
COpenGLProjectView::~COpenGLProjectView() {}
BOOL COpenGLProjectView::PreCreateWindow(CREATESTRUCT& cs) { return CView::PreCreateWindow(cs); }

// COpenGLProjectView 洹몃━湲�
void COpenGLProjectView::OnDraw(CDC* /*pDC*/)
{
	COpenGLProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �뿬湲곗뿉 �썝�떆 �뜲�씠�꽣�뿉 ����븳 洹몃━湲� 肄붾뱶瑜� 異붽���빀�땲�떎.
	DrawGLScene();
	Invalidate(FALSE);
}

// COpenGLProjectView �씤�뇙
void COpenGLProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
BOOL COpenGLProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 湲곕낯�쟻�씤 以�鍮�
	return DoPreparePrinting(pInfo);
}
void COpenGLProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �씤�뇙�븯湲� �쟾�뿉 異붽�� 珥덇린�솕 �옉�뾽�쓣 異붽���빀�땲�떎.
}
void COpenGLProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �씤�뇙 �썑 �젙由� �옉�뾽�쓣 異붽���빀�땲�떎.
}
void COpenGLProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
void COpenGLProjectView::OnDestroy()
{
	CView::OnDestroy();

	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}

// COpenGLProjectView 吏꾨떒
#ifdef _DEBUG
void COpenGLProjectView::AssertValid() const { CView::AssertValid(); }
void COpenGLProjectView::Dump(CDumpContext& dc) const { CView::Dump(dc); }
COpenGLProjectDoc* COpenGLProjectView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLProjectDoc)));
	return (COpenGLProjectDoc*)m_pDocument;
}
#endif _DEBUG

int COpenGLProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �뿬湲곗뿉 �듅�닔�솕�맂 �옉�꽦 肄붾뱶瑜� 異붽���빀�땲�떎.
	m_hDC = GetDC()->m_hDC;

	if (!SetDevicePixelFormat(m_hDC)) {
		return -1;
	}

	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);

	initGL();

	return 0;
}

void COpenGLProjectView::initGL()
{
	TRACE0("initGL �떆�옉\n");
	cameraController.AttachTarget(&camera);

	// GLEW瑜� �궗�슜�븯湲� �쟾�뿉 癒쇱�� 珥덇린�솕�빀�땲�떎
	GLenum err = glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);



	// Shader 媛앹껜瑜� �깮�꽦�빀�땲�떎. �씤�옄濡� �꽆寃⑥＜�뒗 string�뿉 �빐�떦�븯�뒗 glsl�뙆�씪�쓣 �뎽�씠�뜑濡� �궗�슜�빀�땲�떎
	glslShader = Shader("LightingVertexShader.glsl", "LightingFragmentShader.glsl");
	// �빐�떦�븯�뒗 �뎽�씠�뜑瑜� �궗�슜�븯�젮硫� 諛섎뱶�떆 �샇異쒗빐�빞 �빀�땲�떎
	glslShader.use();
	/*
		吏��젙�븳 寃쎈줈�뿉 �엳�뒗 .obj �뙆�씪 �븯�굹瑜� Object 媛앹껜濡� 留뚮뱾�뼱�꽌 ����옣�빀�땲�떎
		Object 媛앹껜濡� ����옣�떆�뿉 洹� 媛앹껜媛� �궗�슜�븷 Shader瑜� �씤�옄濡� �꽆寃⑥빞 �빀�땲�떎
		����옣�븳 Object 媛앹껜瑜� ObjectManager �겢�옒�뒪�쓽 map�뿉 吏묒뼱�꽔�뒿�땲�떎
	*/
	ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/IronMan.obj");
	// ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/Kizuna/kizunaai.obj");
	// ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/Air/Aircraft.obj");
	// ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/h/Handgun.obj");

	/*
		Light 媛앹껜瑜� �깮�꽦�빀�땲�떎 LightingFragmentShader瑜� �궗�슜�빐�빞 �쟻�슜�맗�땲�떎
		�궗�슜�븷 �뎽�씠�뜑, �쐞移�, ambient, diffuse, specular 媛믪쓣 �씤�옄濡� �꽆源곷땲�떎
	*/
	light0 = Light(glslShader, 0, 100, 50, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

	// Skybox Shader 諛� 媛앹껜 �깮�꽦
	{
		// skybox留� �젋�뜑留곹븯�뒗 Shader瑜� �깮�꽦�빀�땲�떎
		skyboxShader = Shader("SkyboxVS.glsl", "SkyboxFS.glsl");
		skyboxShader.use();
		// �뤃�뜑�뿉 �엳�뒗 �뀓�뒪泥섎�� �궗�슜�븯�뿬 Skybox 媛앹껜瑜� 留뚮벊�땲�떎
		skybox0 = Skybox(skyboxShader, "../OpenGLProject/Asset/Skyboxes/BerzeliiPark");
	}

	TRACE0("濡쒕뵫 醫낅즺\n");
}

// OnCreate �씠�썑�뿉 �쟻�뼱�룄 �븳踰� �샇異쒕맗�땲�떎, �솕硫댁쓽 �겕湲곌�� 蹂��븯硫� �샇異쒕맗�땲�떎
void COpenGLProjectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �뿬湲곗뿉 硫붿떆吏� 泥섎━湲� 肄붾뱶瑜� 異붽���빀�땲�떎.
	ReSizeGLScene(cx, cy);
}
// OnSize�뿉�꽌 �샇異쒕맗�땲�떎, �솕硫댁쓽 �겕湲곌�� 蹂��븯硫� �샇異쒕맗�땲�떎
void COpenGLProjectView::ReSizeGLScene(GLsizei width, GLsizei height)
{
	// don't want a divide by zero
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height); // MFC �쟾泥� 李쎌쓽 �겕湲곌�� 蹂��븯硫� 洹몄뿉 留욎떠�꽌 OpenGL濡� 洹몃┫ �솕硫댁쓽 �겕湲곕룄 蹂��솕�떆�궢�땲�떎
	/*
		Viewport�쓽 �겕湲곌�� 蹂��뻽�쑝誘�濡� 洹몄뿉 留욎떠�꽌 移대찓�씪媛� 李띿쓣 Projection matrix�룄 �깉濡� 怨꾩궛�빀�땲�떎
		怨꾩궛�븳 Projection maxtrix瑜� �쁽�옱 �궗�슜以묒씤 Shader�뿉�꽌 Uniform mat4濡� 吏��젙�맂 projection 蹂��닔�뿉 �쟾�떖�빀�땲�떎
		Shader�쓽 projection Uniform 蹂��닔�뒗 VertexShader�뿉 �엳�뒿�땲�떎
	*/
	mat4 projection = perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	glslShader.setMatrix4(projection, "projection");
	skyboxShader.setMatrix4(projection, "u_Projection");
}

// 二쇨린�쟻�쑝濡� �샇異쒕릺�뒗 �븿�닔�엯�땲�떎 �뿬湲곗뿉 洹몃┝�쓣 洹몃┰�땲�떎
void COpenGLProjectView::DrawGLScene(void)
{
	/*
		Controller�뒗 �봽�젅�엫媛� �떆媛꾩감瑜� 怨꾩궛�빀�땲�떎
		移대찓�씪�쓽 ���吏곸엫�룄 �뿬湲곗꽌 �쟻�슜�릺誘�濡� �젣�씪 癒쇱�� �샇異쒗빐�빞 �떎
	*/
	_SystemMangement_::Clock();
	auto cinfo = cameraController.GetControl_info();
	cameraController.GetControllTarget()->Initialize(cinfo);
	cinfo->clickPoint = { 0,0 };

	// claer screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LESS);
	glslShader.use();
	/*
		移대찓�씪�쓽 �쐞移섏�� 媛곷룄�뿉 �뵲瑜� local 醫뚰몴怨꾨�� world 醫뚰몴怨꾨줈 蹂��솚�븳 matrix瑜� 怨꾩궛�빀�땲�떎
		Controller �겢�옒�뒪�뿉�꽌 留덉슦�뒪, �궎蹂대뱶 �엯異쒕젰�뿉 �뵲�씪 Camera �겢�옒�뒪�쓽 �쐞移섍컪, �젙硫� 踰≫꽣 媛믪쓣 蹂��솕�떆�궢�땲�떎
		�뿬湲곗뿉�꽌 View Matrix瑜� 怨꾩궛�븯怨� �쁽�옱 �궗�슜以묒씤 Shader�뿉�꽌 Uniform mat4濡� 吏��젙�맂 view 蹂��닔�뿉 �쟾�떖�빀�땲�떎
		Shader�쓽 view Uniform 蹂��닔�뒗 VertexShader�뿉 �엳�뒿�땲�떎
	*/
	mat4 view = camera.getViewMatrix();
	glslShader.setMatrix4(view, "view");

	/*
		ObjectManager �겢�옒�뒪�뒗 Object 媛앹껜�뱾�쓣 map�뿉�떎媛� ����옣�빐�끉 �긽�깭�엯�땲�떎
		����옣�맂 Object 媛앹껜�뱾�쓣 李⑤�����濡� 洹몃┰�땲�떎
		�궗�슜�븷 Shader瑜� �씤�옄濡� �꽆源곷땲�떎
	*/
	ObjectManager::DrawObjects(glslShader);

	glDepthFunc(GL_LEQUAL); // Object媛� 洹몃젮吏�吏� �븡��� 遺�遺꾩뿉 Skybox媛� 洹몃젮吏묐땲�떎
	skyboxShader.use(); // �뼱�뒓 Shader瑜� �궗�슜�빐�꽌 洹몃┫嫄댁�� �꽕�젙�빀�땲�떎
	view = glm::mat4(glm::mat3(camera.getViewMatrix())); // View�쓽 �씠�룞��� �쟻�슜�븯吏� �븡湲� �쐞�빐 w�슂�냼瑜� �젣嫄고빀�땲�떎
	skyboxShader.setMatrix4(view, "u_View");
	skybox0.Draw(); // �빐�떦 skybox瑜� 洹몃┰�땲�떎

	glslShader.use();
	// swap buffer
	SwapBuffers(m_hDC);
}

// MFC�쓽 �냽�꽦李쎌뿉�꽌 �궇�씪�삤�뒗 硫붿떆吏��엯�땲�떎 李⑦썑�뿉 �븘�슂�븯硫� 援ы쁽�빀�땲�떎
afx_msg LRESULT COpenGLProjectView::OnUwmCustom1(WPARAM wParam, LPARAM lParam)
{
	//CString msg = _T("");
	//msg.Format(_T("Button Click!"));
	return 0;
}
afx_msg LRESULT COpenGLProjectView::OnUwmChecked(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// 留덉슦�뒪 諛� �궎蹂대뱶 �엯異쒕젰��� OpenGLProjectView.cpp�뿉�꽌 諛쏆븘�꽌 Controller �겢�옒�뒪濡� �꽆湲곌퀬 Controller �겢�옒�뒪�뿉�꽌 泥섎━�빀�땲�떎
void COpenGLProjectView::OnRButtonDown(UINT nFlags, CPoint point) { cameraController.OnRButtonDown(nFlags, point); }
void COpenGLProjectView::OnRButtonUp(UINT nFlags, CPoint point)
{
	cameraController.OnRButtonUp(nFlags, point);
	// �슦�겢由� �셿猷뚯떆 踰쀬뼱�굹�젮硫� 二쇱꽍�쓣 吏��썙�빞�븳�떎
	// ClientToScreen(&point);
	// OnContextMenu(this, point);
}
void COpenGLProjectView::OnMouseMove(UINT nFlags, CPoint point) { cameraController.OnMouseMove(nFlags, point); }
void COpenGLProjectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { cameraController.OnKeyDown(nChar, nRepCnt, nFlags); }