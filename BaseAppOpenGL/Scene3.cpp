#include "Scene3.h"

CScene3::CScene3()
{
	int i = 0;
	int size = sizeof(vfCasaVerts) / sizeof(float);
	ofstream outFile; 
	outFile.open("Normals.txt", ios::out | ios::app);
	while (i < size)
	{
		glm::vec3 p1, p2, p3, N;
		p1.x = vfCasaVerts[i++];
		p1.y = vfCasaVerts[i++];
		p1.z = vfCasaVerts[i++];

		p2.x = vfCasaVerts[i++];
		p2.y = vfCasaVerts[i++];
		p2.z = vfCasaVerts[i++];

		p3.x = vfCasaVerts[i++];
		p3.y = vfCasaVerts[i++];
		p3.z = vfCasaVerts[i++];

		N = CalculateTriangleNormalVector(p1, p2, p3);

		outFile << N.x << ", " << N.y << ", " << N.z << ", " << endl;
		outFile << N.x << ", " << N.y << ", " << N.z << ", " << endl;
		outFile << N.x << ", " << N.y << ", " << N.z << ", " << endl;
	}	
	outFile.close();

	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.2f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();
	pTextures->CreateTextureAnisotropic(0, "../Scene3/CasaTex.jpg");
	pTextures->CreateTextureAnisotropic(1, "../Scene1/grass.bmp");
	pTextures->CreateTextureAnisotropic(2, "../Scene3/gold.jpg");
	pTextures->CreateTextureAnisotropic(3, "../Scene3/ruby.jpg");


	fRotY = 0.0f;
	// Exercicio 5
	/*fPosX = -100.0f;
	fPosY = 15.0f;
	fPosZ = 0.0f;

	fPosX1 = 100.0f;
	fPosY1 = 15.0f;
	fPosZ1 = 0.0f;

	fPosX2 = 0.0f;
	fPosY2 = 15.0f;
	fPosZ2 = -100.0f;

	bState = false;*/

	/////

	// Exercicio 6
	/*fPosX = -10.0f;
	fPosY = 7.0f;
	fPosZ = 5.0f;

	fPosX1 = 10.0f;
	fPosY1 = 7.0f;
	fPosZ1 = 5.0f;

	fPosX2 = 0.0f;
	fPosY2 = 7.0f;
	fPosZ2 = -10.0f;

	iAngle = 0.0f;

	bState = false;*/

	////

	// Definição das configurações da fonte de luz (EMISSOR)

	LightAmbient[0] = 1.0f; LightAmbient[1] = 0.0f; LightAmbient[2] = 0.0f; LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f; LightDiffuse[1] = 0.0f; LightDiffuse[2] = 0.0f; LightDiffuse[3] = 1.0f;
	LightSpecular[0] = 1.0f; LightSpecular[1] = 0.0f; LightSpecular[2] = 0.0f; LightSpecular[3] = 1.0f;
	LightPosition[0] = fPosX; LightPosition[1] = fPosY; LightPosition[2] = fPosZ; LightPosition[3] = 1.0f;

	LightAmbient1[0] = 0.0f; LightAmbient1[1] = 1.0f; LightAmbient1[2] = 0.0f; LightAmbient1[3] = 1.0f;
	LightDiffuse1[0] = 0.0f; LightDiffuse1[1] = 1.0f; LightDiffuse1[2] = 0.0f; LightDiffuse1[3] = 1.0f;
	LightSpecular1[0] = 0.0f; LightSpecular1[1] = 1.0f; LightSpecular1[2] = 0.0f; LightSpecular1[3] = 1.0f;
	LightPosition1[0] = fPosX1; LightPosition1[1] = fPosY1; LightPosition1[2] = fPosZ1; LightPosition1[3] = 1.0f;

	LightAmbient2[0] = 0.0f; LightAmbient2[1] = 0.0f; LightAmbient2[2] = 1.0f; LightAmbient2[3] = 1.0f;
	LightDiffuse2[0] = 0.0f; LightDiffuse2[1] = 0.0f; LightDiffuse2[2] = 1.0f; LightDiffuse2[3] = 1.0f;
	LightSpecular2[0] = 0.0f; LightSpecular2[1] = 0.0f; LightSpecular2[2] = 1.0f; LightSpecular2[3] = 1.0f;
	LightPosition2[0] = fPosX2; LightPosition2[1] = fPosY2; LightPosition2[2] = fPosZ2; LightPosition2[3] = 1.0f;

	spotlightPosition[0] = fPosX; spotlightPosition[0] = fPosY; spotlightPosition[0] = fPosZ; spotlightPosition[0] = 1.0f;
	spotlightDirection[0] = 0.0f; spotlightDirection[1] = -1.0f; spotlightDirection[2] = 0.0f;
	spotlightAmbient[0] = 1.0f; spotlightAmbient[1] = 0.0f; spotlightAmbient[2] = 0.0f; spotlightAmbient[3] = 1.0f;
	spotlightDiffuse[0] = 1.0f; spotlightDiffuse[1] = 0.0f; spotlightDiffuse[2] = 0.0f; spotlightDiffuse[3] = 1.0f;
	spotlightSpecular[0] = 1.0f; spotlightSpecular[1] = 0.0f; spotlightSpecular[2] = 0.0f; spotlightSpecular[3] = 1.0f;
	spotlightCutoff = 30.0f;
	spotlightExponent = 5.0f;

	spotlightPosition1[0] = fPosX1; spotlightPosition1[0] = fPosY1; spotlightPosition1[0] = fPosZ1; spotlightPosition1[0] = 1.0f;
	spotlightDirection1[0] = 0.0f; spotlightDirection1[1] = -1.0f; spotlightDirection1[2] = 0.0f;
	spotlightAmbient1[0] = 0.0f; spotlightAmbient1[1] = 1.0f; spotlightAmbient1[2] = 0.0f; spotlightAmbient1[3] = 1.0f;
	spotlightDiffuse1[0] = 0.0f; spotlightDiffuse1[1] = 1.0f; spotlightDiffuse1[2] = 0.0f; spotlightDiffuse1[3] = 1.0f;
	spotlightSpecular1[0] = 0.0f; spotlightSpecular1[1] = 1.0f; spotlightSpecular1[2] = 0.0f; spotlightSpecular1[3] = 1.0f;
	spotlightCutoff1 = 30.0f;
	spotlightExponent1 = 5.0f;

	spotlightPosition2[0] = fPosX2; spotlightPosition2[0] = fPosY2; spotlightPosition2[0] = fPosZ2; spotlightPosition2[0] = 1.0f;
	spotlightDirection2[0] = 0.0f; spotlightDirection2[1] = -1.0f; spotlightDirection2[2] = 0.0f;
	spotlightAmbient2[0] = 0.0f; spotlightAmbient2[1] = 0.0f; spotlightAmbient2[2] = 1.0f; spotlightAmbient2[3] = 1.0f;
	spotlightDiffuse2[0] = 0.0f; spotlightDiffuse2[1] = 0.0f; spotlightDiffuse2[2] = 1.0f; spotlightDiffuse2[3] = 1.0f;
	spotlightSpecular2[0] = 0.0f; spotlightSpecular2[1] = 0.0f; spotlightSpecular2[2] = 1.0f; spotlightSpecular2[3] = 1.0f;
	spotlightCutoff2 = 30.0f;
	spotlightExponent2 = 5.0f;

	// Definição das configurações do material do objeto (REFLEXÂO)
	MatAmbient[0] = 0.2f; MatAmbient[1] = 0.2f; MatAmbient[2] = 0.2f; MatAmbient[3] = 1.0f;
	MatDiffuse[0] = 0.8f; MatDiffuse[1] = 0.8f; MatDiffuse[2] = 0.8f; MatDiffuse[3] = 1.0f;
	MatSpecular[0] = 1.0f; MatSpecular[1] = 1.0f; MatSpecular[2] = 1.0f; MatSpecular[3] = 1.0f;
	MatShininess = 128.0f;

}


CScene3::~CScene3(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}




int CScene3::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glColor4ub(255, 255, 255, 255);

	
	// Exercicio 5
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING); //  Habilita iluminação
	//
	//// Desenha lâmpada 1  ////
	//spotlightPosition[0] = fPosX;
	//spotlightPosition[1] = fPosY;
	//spotlightPosition[2] = fPosZ;
	//spotlightPosition[3] = 1.0f;

	//// Desenha lâmpada 2 ////
	//spotlightPosition1[0] = fPosX1;
	//spotlightPosition1[1] = fPosY1;
	//spotlightPosition1[2] = fPosZ1;
	//spotlightPosition1[3] = 1.0f;

	//// Desenha lâmpada 3 ////
	//spotlightPosition2[0] = fPosX2;
	//spotlightPosition2[1] = fPosY2;
	//spotlightPosition2[2] = fPosZ2;
	//spotlightPosition2[3] = 1.0f;

	//
	//glLightfv(GL_LIGHT0, GL_POSITION, spotlightPosition);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightDirection);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlightCutoff);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotlightExponent);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, spotlightDiffuse);
	//glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT1, GL_POSITION, spotlightPosition1);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection1);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlightCutoff1);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotlightExponent1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlightDiffuse1);
	//glEnable(GL_LIGHT1);

	//glLightfv(GL_LIGHT2, GL_POSITION, spotlightPosition2);
	//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection2);
	//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotlightCutoff2);
	//glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotlightExponent2);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, spotlightDiffuse2);
	//glEnable(GL_LIGHT2);

	//// Atribui os parâmetros de reflexão  do objeto
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	//// Desenha grid 200
	//Draw3DSGrid(200.0f, 200.0f);

	//if (fPosX <= 0 && bState == false) {
	//	fPosX++;
	//	fPosX1--;
	//	fPosZ2++;
	//	if (fPosX == 0) {
	//		bState = true;
	//	}
	//}
	//if (fPosX >= -100 && bState == true) {
	//	fPosX--;
	//	fPosX1++;
	//	fPosZ2--;
	//	if (fPosX == -100) {
	//		bState = false;
	//	}
	//}

	//glDisable(GL_LIGHT0); // Desabilita a luz 0	
	//glDisable(GL_LIGHT1);
	//glDisable(GL_LIGHT2);
	//glDisable(GL_LIGHTING); //  Desabilita iluminação

	// Fim exercicio 5


	// Exercicio 6
	
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);

	//glPushMatrix();
	//glRotatef(iAngle, 0, 1, 0);
	//// Desenha lâmpada 1  ////
	//LightPosition[0] = fPosX;
	//LightPosition[1] = fPosY;
	//LightPosition[2] = fPosZ;
	//LightPosition[3] = 1.0f;

	//// Desenha lâmpada 2 ////
	//LightPosition1[0] = fPosX1;
	//LightPosition1[1] = fPosY1;
	//LightPosition1[2] = fPosZ1;
	//LightPosition1[3] = 1.0f;

	//// Desenha lâmpada 3 ////
	//LightPosition2[0] = fPosX2;
	//LightPosition2[1] = fPosY2;
	//LightPosition2[2] = fPosZ2;
	//LightPosition2[3] = 1.0f;

	//// Atribui os parâmetros da luz 0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	//glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	//glEnable(GL_LIGHT0); // Habilita a luz 0

	//// Atribui os parâmetros da luz 1
	//glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular1);
	//glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	//glEnable(GL_LIGHT1); // Habilita a luz 1

	//// Atribui os parâmetros da luz 2
	//glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpecular2);
	//glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	//glEnable(GL_LIGHT2); // Habilita a luz 2

	//glPushMatrix();
	//glColor3ub(255, 0, 0);
	//glTranslatef(LightPosition[0], LightPosition[1], LightPosition[2]);
	//glutSolidSphere(0.2, 10, 10);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3ub(0, 255, 0);
	//glTranslatef(LightPosition1[0], LightPosition1[1], LightPosition1[2]);
	//glutSolidSphere(0.2, 10, 10);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3ub(0, 0, 255);
	//glTranslatef(LightPosition2[0], LightPosition2[1], LightPosition2[2]);
	//glutSolidSphere(0.2, 10, 10);
	//glPopMatrix();
	//glPopMatrix();
	//

	//// Atribui os parâmetros de reflexão  do objeto
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	//glEnable(GL_TEXTURE_2D);
	//pTextures->ApplyTexture(2);

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	//// Desenha os objetos com a definição do material específico
	//glPushMatrix();
	//glTranslatef(0.0f, 5.0f, 0.0f);
	//glutSolidTeapot(5.0);
	//glPopMatrix();

	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_LIGHTING);
	//	
	//iAngle++;
	//if (iAngle == 360.0f) {
	//	iAngle = 0.0f;
	//}
	
	// Final exercicio 6


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);




	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene3::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;


}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene3::Draw3DSGrid(float width, float length)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene3::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene3::DrawCube()
{
	glBegin(GL_QUADS);
	// face frente
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// face trás
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);


	// face esquerda
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}


void CScene3::DrawPyramid()
{
	glBegin(GL_TRIANGLES);

	// Face frente
	glColor4ub(222, 58, 219, 255);
	glm::vec3 normal = CalculateTriangleNormalVector(
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f));
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face direita
	glColor4ub(181, 147, 54, 255);
	normal = CalculateTriangleNormalVector(
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f));
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face esquerda
	glColor4ub(50, 160, 168, 255);
	normal = CalculateTriangleNormalVector(
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f));
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// Face trás
	normal = CalculateTriangleNormalVector(
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.0f, 0.5f, 0.0f));
	glNormal3f(normal.x, normal.y, normal.z);
	glColor4ub(14, 201, 45, 255);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}


glm::vec3 CScene3::CalculateTriangleNormalVector(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	/*
			   p3
			   /\
			  /  \
			 /    \
			/      \
			+------+
		   p1      p2
	*/

	// Encontrar os vetores v1 e v2, resultado da subtração dos vetores (p2 - p1) e 
	// (p3 - p1), respectivamente
	glm::vec3 v1, v2;
	v1.x = p2.x - p1.x;
	v1.y = p2.y - p1.y;
	v1.z = p2.z - p1.z;

	v2.x = p3.x - p1.x;
	v2.y = p3.y - p1.y;
	v2.z = p3.z - p1.z;

	// Calcular o Cross Product para achar o vetor Normal (não normalizado)
	glm::vec3 normal;
	normal.x = v1.y * v2.z - v1.z * v2.y;
	normal.y = v1.z * v2.x - v1.x * v2.z;
	normal.z = v1.x * v2.y - v1.y * v2.x;

	// Calcula a magnitude do vetor normal
	double magnitude = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

	// Normaliza o vetor normal
	glm::vec3 normalizedVector;
	normalizedVector.x = normal.x / magnitude;
	normalizedVector.y = normal.y / magnitude;
	normalizedVector.z = normal.z / magnitude;

	// Retorna o vetor Normal (normalizado)
	return normalizedVector;
}