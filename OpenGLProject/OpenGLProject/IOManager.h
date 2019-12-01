#pragma once
#include "ObjectBase.h"
#include "SystemMangement.h"
#include "ShaderManager.h"
/*
	���콺 �� Ű���� ���� ��Ʈ�� ó���� �� Ŭ�������� �ٷ�ϴ�
	�޽����� �ٷ� ���� �� �����Ƿ� �޽����� OpenGLProjectView.cpp���� �ް� �ű⼭ �� Ŭ������ ȣ���մϴ�
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
