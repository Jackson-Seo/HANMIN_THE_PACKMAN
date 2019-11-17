#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	// 유저가 추가한 메시지 입니다
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

// COpenGLProjectView 생성/소멸
COpenGLProjectView::COpenGLProjectView() noexcept { }
COpenGLProjectView::~COpenGLProjectView() {}
BOOL COpenGLProjectView::PreCreateWindow(CREATESTRUCT& cs) { return CView::PreCreateWindow(cs); }

// COpenGLProjectView 그리기
void COpenGLProjectView::OnDraw(CDC* /*pDC*/)
{
	COpenGLProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	Invalidate(FALSE);
}

// COpenGLProjectView 인쇄
void COpenGLProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
BOOL COpenGLProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}
void COpenGLProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}
void COpenGLProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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

// COpenGLProjectView 진단
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
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
	TRACE0("initGL 시작\n");
	Controller::Initialize(); // Controller에서 deltaTime을 계산하기 전에 먼저 time을 초기화시킵니다

	// GLEW를 사용하기 전에 먼저 초기화합니다
	GLenum err = glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Shader 객체를 생성합니다. 인자로 넘겨주는 string에 해당하는 glsl파일을 쉐이더로 사용합니다
	glslShader = Shader("LightingVertexShader.glsl", "LightingFragmentShader.glsl");
	// 해당하는 쉐이더를 사용하려면 반드시 호출해야 합니다
	glslShader.use();
	/*
		지정한 경로에 있는 .obj 파일 하나를 Object 객체로 만들어서 저장합니다
		Object 객체로 저장시에 그 객체가 사용할 Shader를 인자로 넘겨야 합니다
		저장한 Object 객체를 ObjectController 클래스의 map에 집어넣습니다
	*/
	// ObjectController::LoadObject(glslShader, "../OpenGLProject/Asset/IronMan.obj");
	// ObjectController::LoadObject(glslShader, "../OpenGLProject/Asset/Kizuna/kizunaai.obj");
	// ObjectController::LoadObject(glslShader, "../OpenGLProject/Asset/Air/Aircraft.obj");
	// ObjectController::LoadObject(glslShader, "../OpenGLProject/Asset/h/Handgun.obj");
	
	/*
		Light 객체를 생성합니다 LightingFragmentShader를 사용해야 적용됩니다
		사용할 쉐이더, 위치, ambient, diffuse, specular 값을 인자로 넘깁니다
	*/
	light0 = Light(glslShader, 0, 100, 50, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

	TRACE0("로딩 종료\n");
}

// OnCreate 이후에 적어도 한번 호출됩니다, 화면의 크기가 변하면 호출됩니다
void COpenGLProjectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}
// OnSize에서 호출됩니다, 화면의 크기가 변하면 호출됩니다
void COpenGLProjectView::ReSizeGLScene(GLsizei width, GLsizei height)
{
	// don't want a divide by zero
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height); // MFC 전체 창의 크기가 변하면 그에 맞춰서 OpenGL로 그릴 화면의 크기도 변화시킵니다
	/*
		Viewport의 크기가 변했으므로 그에 맞춰서 카메라가 찍을 Projection matrix도 새로 계산합니다
		계산한 Projection maxtrix를 현재 사용중인 Shader에서 Uniform mat4로 지정된 projection 변수에 전달합니다
		Shader의 projection Uniform 변수는 VertexShader에 있습니다
	*/
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	glslShader.setMatrix4(projection, "projection");
}

// 주기적으로 호출되는 함수입니다 여기에 그림을 그립니다
void COpenGLProjectView::DrawGLScene(void)
{
	/*
		Controller는 프레임간 시간차를 계산합니다
		카메라의 움직임도 여기서 적용되므로 제일 먼저 호출해야 합니다
	*/
	Controller::Clock();

	// claer screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
		카메라의 위치와 각도에 따른 local 좌표계를 world 좌표계로 변환한 matrix를 계산합니다
		Controller 클래스에서 마우스, 키보드 입출력에 따라 Camera 클래스의 위치값, 정면 벡터 값을 변화시킵니다
		여기에서 View Matrix를 계산하고 현재 사용중인 Shader에서 Uniform mat4로 지정된 view 변수에 전달합니다
		Shader의 view Uniform 변수는 VertexShader에 있습니다
	*/
	glm::mat4 view = Camera::getViewMatrix();
	glslShader.setMatrix4(view, "view");

	Axis::Draw(); // X축, Y축, Z축을 그립니다
	/*
		ObjectController 클래스는 Object 객체들을 map에다가 저장해논 상태입니다
		저장된 Object 객체들을 차례대로 그립니다
		사용할 Shader를 인자로 넘깁니다
	*/
	ObjectController::DrawObjects(glslShader);

	// swap buffer
	SwapBuffers(m_hDC);
}

// MFC의 속성창에서 날라오는 메시지입니다 차후에 필요하면 구현합니다
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

// 마우스 및 키보드 입출력은 OpenGLProjectView.cpp에서 받아서 Controller 클래스로 넘기고 Controller 클래스에서 처리합니다
void COpenGLProjectView::OnRButtonDown(UINT nFlags, CPoint point) { Controller::OnRButtonDown(nFlags, point); }
void COpenGLProjectView::OnRButtonUp(UINT nFlags, CPoint point) {
	Controller::OnRButtonUp(nFlags, point);
	// 우클릭 완료시 벗어나려면 주석을 지워야한다
	// ClientToScreen(&point);
	// OnContextMenu(this, point);
}
void COpenGLProjectView::OnMouseMove(UINT nFlags, CPoint point) { Controller::OnMouseMove(nFlags, point); }
void COpenGLProjectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { Controller::OnKeyDown(nChar, nRepCnt, nFlags); }