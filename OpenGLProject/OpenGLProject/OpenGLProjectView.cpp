#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OpenGLProject.h"
#endif

#include "OpenGLProjectDoc.h"
#include "OpenGLProjectView.h"

float deltay = 0.0f;
float objNum[MAXOBJ][3];
const float objAreaMin = -500.0f;
const float objAreaMax = 500.0f;

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
	ON_COMMAND(ID_SHADER_PHONGSHADING, &COpenGLProjectView::OnShaderPhongShading)
	ON_COMMAND(ID_SHADER_RAYTRACINGRENDERING, &COpenGLProjectView::OnShaderRayTracingRendering)
	ON_UPDATE_COMMAND_UI(ID_SHADER_PHONGSHADING, &COpenGLProjectView::OnUpdateShaderPhongshading)
	ON_UPDATE_COMMAND_UI(ID_SHADER_RAYTRACINGRENDERING, &COpenGLProjectView::OnUpdateShaderRaytracingrendering)
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
	// CString sirenCall("../OpenGLProject/Asset/soundtrack/Tornado_Siren_II-Delilah-747233690.wav");
	// PlaySound(sirenCall, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);

	TRACE0("initGL 시작\n");

	// GLEW를 사용하기 전에 먼저 초기화합니다
	GLenum err = glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	shaderManager = new ShaderManager();
	ioManager.Initialize(shaderManager);
	ioManager.AttachTarget(&camera);
	// 해당하는 쉐이더를 사용하려면 반드시 호출해야 합니다
	shaderManager->glslShader.use();
	/*
		지정한 경로에 있는 .obj 파일 하나를 Object 객체로 만들어서 저장합니다
		Object 객체로 저장시에 그 객체가 사용할 Shader를 인자로 넘겨야 합니다
		저장한 Object 객체를 ObjectManager 클래스의 map에 집어넣습니다
	*/
	// ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/Air/Imperial_Exekutor_Class/StarDestroyer_Exekutorclass.obj", 0);
	// ObjectManager::LoadObject(glslShader, "../OpenGLProject/Asset/Air/fighter/FuturisticCombatJet.obj", 0);
	//ObjectManager::LoadObject(shaderManager->glslShader, "../OpenGLProject/Asset/Air/miniAirFighter/Aircraft.obj", 0);
	ObjectManager::LoadObject(shaderManager->glslShader, "../OpenGLProject/Asset/IronMan.obj", 0);
	airobj = ObjectManager::s_object[0];

	for (int index = 0; index < MAXOBJ; index++) {
		objNum[index][0] = _SystemMangement_::getRandomNumber(objAreaMin, objAreaMax);
		objNum[index][1] = _SystemMangement_::getRandomNumber(-30, objAreaMax);
		objNum[index][2] = _SystemMangement_::getRandomNumber(objAreaMin, objAreaMax);
	}

	 //디폴트 plane 초기화
	 planeShader = Shader("planeVS.glsl", "planeFS.glsl");
	 defaultPlane.settingPlane();

	/*
		Light 객체를 생성합니다 LightingFragmentShader를 사용해야 적용됩니다
		사용할 쉐이더, 위치, ambient, diffuse, specular 값을 인자로 넘깁니다
	*/
	light0 = Light(shaderManager->glslShader, 0, 100, 50, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

	// Skybox Shader 및 객체 생성
	{
		// 폴더에 있는 텍스처를 사용하여 Skybox 객체를 만듭니다
		skybox0 = Skybox(shaderManager->skyboxShader, "../OpenGLProject/Asset/Skyboxes/Skybox_Space");
		// skybox0 = Skybox(shaderManager->skyboxShader, "../OpenGLProject/Asset/Skyboxes/BonoBono");
		skybox0.ShareTexture(shaderManager->rayTracingShader);
		// GPGPU를 작동시키기 위해 Skybox의 Vertex만 넘겨줍니다
		skybox0.ShareTexture(shaderManager->gpgpuShader);
	}
	// Ray Tracing을 위한 세팅입니다
	{
		shaderManager->rayTracingShader.use();
		light1 = Light(shaderManager->rayTracingShader, 0, 0, 0, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		shaderManager->rayTracingShader.setVec3(glm::vec3(0.2f, 0.0f, 0.0f), "material.ambient");
		shaderManager->rayTracingShader.setVec3(glm::vec3(0.2f, 0.0f, 0.0f), "material.diffuse");
		shaderManager->rayTracingShader.setVec3(glm::vec3(0.8f), "material.specular");
		shaderManager->rayTracingShader.setfloat(1.0f, "material.shininess");
		// Rendering할 물체들을 그립니다
		makeArr();
	}
	TRACE0("로딩 종료\n");
}

// OnCreate 이후에 적어도 한번 호출됩니다, 화면의 크기가 변하면 호출됩니다
void COpenGLProjectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	ioManager.OnSize(nType, cx, cy);

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
	float fovy = 45.0f;
	mat4 projection = perspective(fovy, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	glslShader.setMatrix4(projection, "projection");
    planeShader.use();
	planeShader.setMatrix4(projection, "projection");
	shaderManager->glslShader.use();
	shaderManager->glslShader.setMatrix4(projection, "projection");
	shaderManager->skyboxShader.use();
	shaderManager->skyboxShader.setMatrix4(projection, "u_Projection");
	shaderManager->rayTracingShader.use();
	shaderManager->rayTracingShader.setUniform1i(width * 0.5f, "u_ScreenWidthHalf");
	shaderManager->rayTracingShader.setUniform1i(height * 0.5f, "u_ScreenHeightHalf");
	shaderManager->rayTracingShader.setUniform1f((height * 0.5f) / glm::tan(fovy * 0.5f), "u_Distance");
	shaderManager->rayTracingShader.setMatrix4(projection, "u_Projection");
}

// 주기적으로 호출되는 함수입니다 여기에 그림을 그립니다
void COpenGLProjectView::DrawGLScene(void)
{
	/*
		_SystemManagement는 매 프레임간 시간차를 계산합니다
	*/
	_SystemMangement_::Clock();
	auto cinfo = ioManager.GetControl_info();
	ioManager.GetControllTarget()->Initialize(cinfo);
	cinfo->clickPoint = { 0,0 };

	// claer screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//모든 오브젝트들의 런타임 무브먼트는 여기서 코딩합니다.
	deltay += _SystemMangement_::deltaTime * 0.004f;

	/*
		IF문 : Ray Tracing 렌더링을 하도록 설정되었나?
		TRUE : Ray Tracing 렌더링을 적용합니다
		FALSE : Phong Shading을 적용합니다
	*/
	if (shaderManager->rtxON) {
		glUseProgram(0);
		shaderManager->rayTracingShader.use();
		// 구의 위치를 World 위치를 설정하고 카메라 좌표계로 변환합니다
		mat4 view = camera.getViewMatrix();
		// Rendering할 vertex에 model과 view 변환을 적용시킵니다
		float arr[219];
		glm::mat4 model = glm::mat4(1.0f); // Identitiy 행렬 설정
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 5.0f)); // Translate
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glm::vec3 tmp;
		for (int i = 0; i < 36; i++) {
			tmp = glm::vec3(view * model * glm::vec4(vertexArr[i], 1.0f));
			arr[i * 3 + 0] = tmp.x;
			arr[i * 3 + 1] = tmp.y;
			arr[i * 3 + 2] = tmp.z;
		}
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, -5.0f)); // Translate
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		for (int i = 36; i < 72; i++) {
			 tmp = glm::vec3(view * model * glm::vec4(vertexArr[i], 1.0f));
			 arr[i * 3 + 0] = tmp.x;
			 arr[i * 3 + 1] = tmp.y;
			 arr[i * 3 + 2] = tmp.z;
		}
		tmp = glm::vec3(view * glm::vec4(vertexArr[72], 1.0f));
		arr[216] = tmp.x;
		arr[217] = tmp.y;
		arr[218] = tmp.z;
		shaderManager->rayTracingShader.setfloatv(arr, 219, "arr");
		TRACE1("\nwho : %d\n", glGetUniformLocation(shaderManager->rayTracingShader.getID(), "arr"));

		// 빛의 위치를 계산하고 Shader에 전달합니다
		glm::vec3 lightPos = glm::vec3(view * glm::vec4(-10, 2, 15, 1));
		light1.setPosition(shaderManager->rayTracingShader, lightPos);

		// RayTracingVS에 Vertex 좌표를 보내줘야 하므로 skybox의 Vertex를 이용합니다
		view = glm::mat4(glm::mat3(view)); // View의 이동은 적용하지 않기 위해 w요소를 제거합니다
		shaderManager->skyboxShader.setMatrix4(view, "u_View");
		skybox0.Draw();
	}
	else {
		glUseProgram(0);
		glDepthFunc(GL_LESS);
		/*
			카메라의 위치와 각도에 따른 local 좌표계를 world 좌표계로 변환한 matrix를 계산합니다
			Controller 클래스에서 마우스, 키보드 입출력에 따라 Camera 클래스의 위치값, 정면 벡터 값을 변화시킵니다
			여기에서 View Matrix를 계산하고 현재 사용중인 Shader에서 Uniform mat4로 지정된 view 변수에 전달합니다
			Shader의 view Uniform 변수는 VertexShader에 있습니다
		*/
		mat4 view = camera.getViewMatrix();
		shaderManager->glslShader.use();
		shaderManager->glslShader.setMatrix4(view, "view");
		planeShader.use();
		planeShader.setMatrix4(view, "view");
		/*
			ObjectManager 클래스는 Object 객체들을 map에다가 저장해논 상태입니다
			저장된 Object 객체들을 차례대로 그립니다
			사용할 Shader를 인자로 넘깁니다
		*/
		shaderManager->glslShader.use();
		for (int i = 0; i < MAXOBJ; i++) {
			ObjectManager::s_object[0].initObjPos(objNum[i][0], objNum[i][1], objNum[i][2]);
			ObjectManager::s_object[0].setObjPos(0.0f, 0.0f, deltay);
			ObjectManager::DrawObjects(shaderManager->glslShader);
		}

		glDepthFunc(GL_LEQUAL); // Object가 그려지지 않은 부분에 Skybox가 그려집니다
		shaderManager->skyboxShader.use(); // 어느 Shader를 사용해서 그릴건지 설정합니다
		view = glm::mat4(glm::mat3(camera.getViewMatrix())); // View의 이동은 적용하지 않기 위해 w요소를 제거합니다
		shaderManager->skyboxShader.setMatrix4(view, "u_View");
		skybox0.Draw(); // 해당 skybox를 그립니다

		planeShader.use();
		defaultPlane.caltranslate(planeShader);
		defaultPlane.drawPlane();
		shaderManager->glslShader.use();
	}
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
void COpenGLProjectView::OnRButtonDown(UINT nFlags, CPoint point) { ioManager.OnRButtonDown(nFlags, point); }
void COpenGLProjectView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ioManager.OnRButtonUp(nFlags, point);
	// 우클릭 완료시 벗어나려면 주석을 지워야한다
	// ClientToScreen(&point);
	// OnContextMenu(this, point);
}
void COpenGLProjectView::OnMouseMove(UINT nFlags, CPoint point) { ioManager.OnMouseMove(nFlags, point); }
void COpenGLProjectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { ioManager.OnKeyDown(nChar, nRepCnt, nFlags); }
void COpenGLProjectView::OnShaderPhongShading() { ioManager.OnShaderPhongShading(); }
void COpenGLProjectView::OnShaderRayTracingRendering() { ioManager.OnShaderRayTracingRendering(); }
void COpenGLProjectView::OnUpdateShaderPhongshading(CCmdUI* pCmdUI) { ioManager.OnUpdateShaderPhongshading(pCmdUI); }
void COpenGLProjectView::OnUpdateShaderRaytracingrendering(CCmdUI* pCmdUI) { ioManager.OnUpdateShaderRaytracingrendering(pCmdUI); }

void COpenGLProjectView::makeArr(void) {
	// Rendering할 물체들을 그립니다
	float Vertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	vertexArr = new glm::vec3[73];
	for (int i = 0; i < 36; i++) {
		vertexArr[i] = glm::vec3(Vertices[i * 3 + 0], Vertices[i * 3 + 1], Vertices[i * 3 + 2]);
		vertexArr[i+36] = glm::vec3(Vertices[i * 3 + 0], Vertices[i * 3 + 1], Vertices[i * 3 + 2]);
	}
	vertexArr[72] = glm::vec3(0, 0, 0);
}
