#pragma once
#include "ObjectBase.h"
#include "SystemMangement.h"
#include "ShaderManager.h"
/*
	마우스 및 키보드 같은 컨트롤 처리는 이 클래스에서 다룹니다
	메시지를 바로 받을 수 없으므로 메시지는 OpenGLProjectView.cpp에서 받고 거기서 이 클래스를 호출합니다
*/

class IOManager : public ObjectBase
{
private:
	Control_info info;
	ObjectBase* ControllTarget;
	ShaderManager* shaderManager;
	GLsizei width;
	GLsizei height;
public:
	IOManager();
	~IOManager() {};
public:
	Control_info* GetControl_info(void);
public:
	void Initialize(ShaderManager* shaderManager);
	void OnSize(UINT nType, int cx, int cy);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnShaderPhongShading(void);
	void OnShaderRayTracingRendering(void);
	void OnUpdateShaderPhongshading(CCmdUI* pCmdUI);
	void OnUpdateShaderRaytracingrendering(CCmdUI* pCmdUI);
	
	void AttachTarget(ObjectBase* obj);
	ObjectBase* GetControllTarget(void);
};
