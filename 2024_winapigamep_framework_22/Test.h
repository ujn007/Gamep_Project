#pragma once
#include"Object.h";
class Texture;	
class Test : public Object
{
public:
	Test();
	~Test();

	// Object��(��) ���� ��ӵ�
	void Update() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
};

