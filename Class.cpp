#include"Class.h"
void DrawTransparentBitmap(HDC hdc,HBITMAP hBitmap,short xStart,short yStart,COLORREF cTransparentColor)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack,bmAndObject,bmAndMem,bmSave,bmBackOld,bmObjectOld,bmMemOld,bmSaveOld;
	HDC hdcMem,hdcBack,hdcObject,hdcTemp,hdcSave;
	POINT ptSize;
	hdcTemp=CreateCompatibleDC(hdc);
	SelectObject(hdcTemp,hBitmap);
	GetObject(hBitmap,sizeof(BITMAP),(LPSTR)&bm);
	ptSize.x=bm.bmWidth;
	ptSize.y=bm.bmHeight;
	DPtoLP(hdcTemp,&ptSize,1);
	hdcBack=CreateCompatibleDC(hdc);
	hdcObject=CreateCompatibleDC(hdc);
	hdcMem=CreateCompatibleDC(hdc);
	hdcSave=CreateCompatibleDC(hdc);
	bmAndBack=CreateBitmap(ptSize.x,ptSize.y,1,1,NULL);
	bmAndObject=CreateBitmap(ptSize.x,ptSize.y,1,1,NULL);
	bmAndMem=CreateCompatibleBitmap(hdc,ptSize.x,ptSize.y);
	bmSave=CreateCompatibleBitmap(hdc,ptSize.x,ptSize.y);
	bmBackOld=(HBITMAP)SelectObject(hdcBack,bmAndBack);
	bmObjectOld=(HBITMAP)SelectObject(hdcObject,bmAndObject);
	bmMemOld=(HBITMAP)SelectObject(hdcMem,bmAndMem);
	bmSaveOld=(HBITMAP)SelectObject(hdcSave,bmSave);
	SetMapMode(hdcTemp,GetMapMode(hdc));
	BitBlt(hdcSave,0,0,ptSize.x,ptSize.y,hdcTemp,0,0,SRCCOPY);
	cColor=SetBkColor(hdcTemp,cTransparentColor);
	BitBlt(hdcObject,0,0,ptSize.x,ptSize.y,hdcTemp,0,0,SRCCOPY);
	SetBkColor(hdcTemp,cColor);
	BitBlt(hdcBack,0,0,ptSize.x,ptSize.y,hdcObject,0,0,NOTSRCCOPY);
	BitBlt(hdcMem,0,0,ptSize.x,ptSize.y,hdc,xStart,yStart,SRCCOPY);
	BitBlt(hdcMem,0,0,ptSize.x,ptSize.y,hdcObject,0,0,SRCAND);
	BitBlt(hdcTemp,0,0,ptSize.x,ptSize.y,hdcBack,0,0,SRCAND);
	BitBlt(hdcMem,0,0,ptSize.x,ptSize.y,hdcTemp,0,0,SRCPAINT);
	BitBlt(hdc,xStart,yStart,ptSize.x,ptSize.y,hdcMem,0,0,SRCCOPY);
	BitBlt(hdcTemp,0,0,ptSize.x,ptSize.y,hdcSave,0,0,SRCCOPY);
	DeleteObject(SelectObject(hdcBack,bmBackOld));
	DeleteObject(SelectObject(hdcObject,bmObjectOld));
	DeleteObject(SelectObject(hdcMem,bmMemOld));
	DeleteObject(SelectObject(hdcSave,bmSaveOld));
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

CDlgUserClass *CDlgUserClass::ptr=NULL;
CDlgUserClass::CDlgUserClass()
{
	ptr=this;
}
LRESULT CALLBACK CDlgUserClass::WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hwnd,WM_DESTROY,ptr->Cls_OnDestroy);
		default: return DefWindowProc(hwnd,msg,wParam,lParam);break;
	}
	return 0;
}
void CDlgUserClass::Cls_OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

CObject::CObject(INT x,INT y,HWND hmain,HDC main,HDC buf):iX(x),iY(y),hMAIN(hmain),MAIN(main),BUF(buf)
{
	iWIDTH=0;
	iHEIGHT=0;
	Bull=NULL;
	bBull=FALSE;
}
void CObject::Show(HBITMAP hBmp)
{
	DrawTransparentBitmap(BUF,hBmp,iX,iY,mask_color);
}
void CObject::Show()
{
}
void CObject::Move()
{
}
CObject::~CObject()
{
}

CGrass::CGrass(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=32;
	hBmp=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Grass));
}
void CGrass::Show()
{
	CObject::Show(hBmp);
}

CBrick::CBrick(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=16;
	hBmp=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Brick));
}
void CBrick::Show()
{
	CObject::Show(hBmp);
}

CWater::CWater(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=32;
	hBmp[0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Wate_0));
	hBmp[1]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Wate_1));
}
void CWater::Show()
{
	if(GetTickCount()%10000<5000)
		CObject::Show(hBmp[0]);
	else
		CObject::Show(hBmp[1]);
}

CConcrete::CConcrete(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=16;
	hBmp=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Concrete));
}
void CConcrete::Show()
{
	CObject::Show(hBmp);
}

CIce::CIce(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=32;
	hBmp=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Wall_Ice));
}
void CIce::Show()
{
	CObject::Show(hBmp);
}

CExplosion_Small::CExplosion_Small(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=32;
	for(int i=0;i<3;i++)
		hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Explosion_Small_0+i));
	iTIMER=0;
}
void CExplosion_Small::Show()
{
	if(iTIMER<6)
		CObject::Show(hBmp[iTIMER/2]);
	iTIMER++;
}

CExplosion_Big::CExplosion_Big(INT x,INT y,HWND hmain,HDC main,HDC buf):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=64;
	for(int i=0;i<6;i++)
		hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Explosion_Big_0+i));
	iTIMER=0;
}
void CExplosion_Big::Show()
{
	if(iTIMER<12)
		CObject::Show(hBmp[iTIMER/2]);
	iTIMER++;
}

CBullet::CBullet(INT x,INT y,HWND hmain,HDC main,HDC buf,INT ispeed,INT idir):CObject(x,y,hmain,main,buf)
{
	iSpeed=ispeed;
	iDir=idir;
	iWIDTH=iHEIGHT=8;
	for(int i=0;i<4;i++)
		hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Bullet_0+i));
}
void CBullet::Move()
{
	switch(iDir)
	{
		case 0:iY-=iSpeed;break;
		case 1:iX+=iSpeed;break;
		case 2:iY+=iSpeed;break;
		case 3:iX-=iSpeed;break;
	}
}
void CBullet::Show()
{
	CObject::Show(hBmp[iDir]);
}

CPlayer_Tank::CPlayer_Tank(INT x,INT y,HWND hmain,HDC main,HDC buf,int type):CObject(x,y,hmain,main,buf)
{
	switch(type)
	{
		case 1:
			iArmor=100;
			iSpeed=2;
			for(int i=0;i<8;i++)
				hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Player_1_T_1_0+i));
			iWIDTH=iHEIGHT=26;
			break;
		case 2:
			iArmor=100;
			iSpeed=3;
			for(int i=0;i<8;i++)
				hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Player_1_T_2_0+i));
			iWIDTH=iHEIGHT=30;
			break;
		case 3:
			iArmor=150;
			iSpeed=3;
			for(int i=0;i<8;i++)
				hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Player_1_T_3_0+i));
			iWIDTH=iHEIGHT=30;
			break;
		case 4:
			iArmor=200;
			iSpeed=4;
			for(int i=0;i<8;i++)
				hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Player_1_T_4_0+i));
			iWIDTH=iHEIGHT=30;
			break;
	};
	iDir=0;
	hCurBmp=hBmp[0];
}
void CPlayer_Tank::Move()
{
	iX_Old=iX;
	iY_Old=iY;
	if(GetAsyncKeyState(VK_UP))
	{
		iY-=iSpeed;
		iDir=0;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[0];
		else
			hCurBmp=hBmp[1];
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		iX+=iSpeed;
		iDir=1;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[2];
		else
			hCurBmp=hBmp[3];
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		iY+=iSpeed;
		iDir=2;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[4];
		else
			hCurBmp=hBmp[5];
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		iX-=iSpeed;
		iDir=3;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[6];
		else
			hCurBmp=hBmp[7];
	}
	if(GetAsyncKeyState(VK_SPACE)&&bBull==FALSE)
		bBull=TRUE;
}
void CPlayer_Tank::Show()
{
	CObject::Show(hCurBmp);
}

CEnemy_Tank::CEnemy_Tank(INT x,INT y,HWND hmain,HDC main,HDC buf,INT Type):CObject(x,y,hmain,main,buf)
{
	iWIDTH=iHEIGHT=30;
	INT iSprite=Enemy_T_1_0;
	iSpeed=1;
	iArmor=100;
	iType=Type;
	switch(iType)
	{
		case 1:
			iSpeed=1;
			iArmor=100;
			iSprite=Enemy_T_1_0;
			break;
		case 2:
			iSpeed=3;
			iSprite=50;
			iSprite=Enemy_T_2_0;
			break;
		case 3:
			iSpeed=1;
			iSprite=200;
			iSprite=Enemy_T_3_0;
			break;
	}
	iDir=2;//rand()%4;
	for(int i=0;i<8;i++)
		hBmp[i]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(iSprite+i));
	hCurBmp=hBmp[4];
	iTIMER_BEGIN=0;
}
void CEnemy_Tank::Move()
{
	iX_Old=iX;
	iY_Old=iY;
	iTIMER_BEGIN++;
	if(iTIMER_BEGIN>iTIMER_END)
	{
		iTIMER_BEGIN=0;
		iTIMER_END=rand()%100;
		iDir=rand()%4;
	}
	if(iDir==0)
	{
		iY-=iSpeed;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[0];
		else
			hCurBmp=hBmp[1];
	}
	if(iDir==1)
	{
		iX+=iSpeed;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[2];
		else
			hCurBmp=hBmp[3];
	}
	if(iDir==2)
	{
		iY+=iSpeed;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[4];
		else
			hCurBmp=hBmp[5];
	}
	if(iDir==3)
	{
		iX-=iSpeed;
		if(GetTickCount()%2==0)
			hCurBmp=hBmp[6];
		else
			hCurBmp=hBmp[7];
	}
	if(bBull==FALSE)
	{
		if(rand()%100==0)
			bBull=TRUE;
	}
}
void CEnemy_Tank::Show()
{
	CObject::Show(hCurBmp);
}

CLevel *CLevel::ptr=NULL;
CLevel::CLevel(HWND hwnd)
{
	ptr=this;
	hMAIN=hwnd;
	MAIN=GetDC(hMAIN);
	hBUFFER=CreateBitmap(425,445,1,32,NULL);
	BUF=CreateCompatibleDC(MAIN);
	SelectObject(BUF,hBUFFER);
	hBmp[0]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Menu_1));
	hBmp[1]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(Menu_2));
	hBmp[2]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(PAUSE));
	hBmp[3]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(GAMEOVER));
	hBmp[4]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(WINER_1));
	hBmp[5]=LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(WINER_2));
	user=0;
	timer=0;
	level=0;
}
CLevel::~CLevel()
{
	for(int i=0;i<AllObj.size();i++)
		delete AllObj[i];
	for(int i=0;i<6;i++)
		DeleteObject(hBmp[i]);
	DeleteObject(hBUFFER);
	DeleteDC(BUF);
	DeleteDC(MAIN);
}
void CLevel::Action()
{
	for(int i=0;i<AllObj.size();i++)
	{
  		AllObj[i]->Move();
		if(typeid(*AllObj[i])==typeid(CPlayer_Tank)||typeid(*AllObj[i])==typeid(CEnemy_Tank))
			if(AllObj[i]->iX<0||AllObj[i]->iY<0||AllObj[i]->iX>=390||AllObj[i]->iY>=390)
			{
				AllObj[i]->iX=AllObj[i]->iX_Old;
				AllObj[i]->iY=AllObj[i]->iY_Old;
				if(typeid(*AllObj[i])==typeid(CEnemy_Tank))
					AllObj[i]->iDir=rand()%4;
			}
			else
				Check_Move(AllObj[i]);
		if(typeid(*AllObj[i])==typeid(CPlayer_Tank)||typeid(*AllObj[i])==typeid(CEnemy_Tank))
		{
			if(AllObj[i]->Bull==NULL&&AllObj[i]->bBull==TRUE)//Если CUR выстрелил но пуля еще не создана
			{
				INT X,Y;
				switch(AllObj[i]->iDir)
				{
					case 0:
						X=AllObj[i]->iX+(AllObj[i]->iWIDTH-8)/2;
						Y=AllObj[i]->iY-8;
						break;
					case 1:
						X=AllObj[i]->iX+AllObj[i]->iWIDTH+1;
						Y=AllObj[i]->iY+(AllObj[i]->iHEIGHT-8)/2;
						break;
					case 2:
						X=AllObj[i]->iX+(AllObj[i]->iWIDTH-8)/2;
						Y=AllObj[i]->iY+AllObj[i]->iHEIGHT+1;
						break;
					case 3:
						X=AllObj[i]->iX-8;
						Y=AllObj[i]->iY+(AllObj[i]->iHEIGHT-8)/2;
						break;
				}
				AllObj[i]->Bull=new CBullet(X,Y,AllObj[i]->hMAIN,AllObj[i]->MAIN,AllObj[i]->BUF,AllObj[i]->iSpeed*2,AllObj[i]->iDir);
			}
			if(AllObj[i]->Bull!=NULL)//Если CUR выстрелил и пуля создана
			{
				AllObj[i]->Bull->Move();
				AllObj[i]->Bull->Show();
				if(AllObj[i]->Bull->iX<0||AllObj[i]->Bull->iX>425||AllObj[i]->Bull->iY<0||AllObj[i]->Bull->iY>445)//Проверка выхода Пули за пределы экрана
				{
					delete AllObj[i]->Bull;
					AllObj[i]->Bull=NULL;
					AllObj[i]->bBull=FALSE;
				}
				else
					Check_Bul(AllObj[i]);
			}
			}
		if(typeid(*AllObj[i])==typeid(CExplosion_Small)&&AllObj[i]->iTIMER>6)
		{
				delete AllObj[i];
				itrAll=AllObj.begin();
				AllObj.erase(itrAll+i);
				i--;
		}
		if(typeid(*AllObj[i])==typeid(CExplosion_Big)&&AllObj[i]->iTIMER>12)
		{
				delete AllObj[i];
				itrAll=AllObj.begin();
				AllObj.erase(itrAll+i);
				i--;
		}
		AllObj[i]->Show();
	}
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		DrawTransparentBitmap(BUF,hBmp[2],100,100,mask_color);
		BitBlt(MAIN,0,0,425,445,BUF,0,0,SRCCOPY);
		bool pausestob=true;
		do
		{
			Sleep(10);
			if(GetAsyncKeyState(VK_ESCAPE))
				pausestob=false;
		}
		while(pausestob);
	}
	if(Enemy_Size<=0)
	{
		level++;
		if(level>5)
			Load_WINNER();
		LOADLEVEL(level);
	}
	BitBlt(MAIN,0,0,425,445,BUF,0,0,SRCCOPY);//Вывод буфера на экран
	PatBlt(BUF,0,0,425,445,BLACKNESS);		 //Очистка экрана
}
void CALLBACK CLevel::TimerProc(HWND hwnd,UINT msg,UINT_PTR idEvent,DWORD dwTimer)
{
	ptr->Action();
}
void CLevel::Check_Move(CObject *CUR)
{
	for(int i=0;i<AllObj.size();i++)
	{
		if(AllObj[i]!=CUR)
		{
			if(typeid(*CUR)==typeid(CEnemy_Tank)||typeid(*CUR)==typeid(CPlayer_Tank))//Если CUR являеться классом CPlayer_Tank или CEnemy_Tank
			{
				if(typeid(*AllObj[i])==typeid(CPlayer_Tank)||typeid(*AllObj[i])==typeid(CEnemy_Tank)||typeid(*AllObj[i])==typeid(CConcrete)||typeid(*AllObj[i])==typeid(CWater)||typeid(*AllObj[i])==typeid(CBrick))//Проверяем непересекаються ли кординаты Стен кирпичной, бетоной, воды или с другим танком
				{
					if(AllObj[i]->iX<CUR->iX+CUR->iWIDTH&&AllObj[i]->iX+AllObj[i]->iWIDTH>CUR->iX&&AllObj[i]->iY<CUR->iY+CUR->iHEIGHT&&AllObj[i]->iY+AllObj[i]->iHEIGHT>CUR->iY)
					{
						CUR->iX=CUR->iX_Old;
						CUR->iY=CUR->iY_Old;
						if(typeid(*CUR)==typeid(CEnemy_Tank))
							CUR->iDir=rand()%4;
					}
				}
			}
		}
	}
}
void CLevel::Check_Bul(CObject *CUR)
{
	for(int i=0;i<AllObj.size();i++)
	{
			if(typeid(*CUR)==typeid(CPlayer_Tank))
			{
				if(typeid(*AllObj[i])==typeid(CEnemy_Tank)||typeid(*AllObj[i])==typeid(CConcrete)||typeid(*AllObj[i])==typeid(CBrick))
				{
					if(AllObj[i]->iX<CUR->Bull->iX+CUR->Bull->iWIDTH&&AllObj[i]->iX+AllObj[i]->iWIDTH>CUR->Bull->iX&&AllObj[i]->iY<CUR->Bull->iY+CUR->Bull->iHEIGHT&&AllObj[i]->iY+AllObj[i]->iHEIGHT>CUR->Bull->iY)
					{
						if(typeid(*AllObj[i])==typeid(CEnemy_Tank))
						{
							AllObj[i]->iArmor-=10;
							if(AllObj[i]->iArmor>0)
							{
								AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
							}
							else
							{
								delete AllObj[i];
								itrAll=AllObj.begin();									
								AllObj.erase(itrAll+i);
								AllObj.push_back(new CExplosion_Big(CUR->Bull->iX-32,CUR->Bull->iY-32,hMAIN,MAIN,BUF));
								Enemy_Size--;
							}
						}
						else if(typeid(*AllObj[i])==typeid(CConcrete))
						{
 							AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
						}
						else if(typeid(*AllObj[i])==typeid(CBrick))
						{
							delete AllObj[i];
							itrAll=AllObj.begin();									
							AllObj.erase(itrAll+i);
							AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
						}
						delete CUR->Bull;
						CUR->Bull=NULL;
						CUR->bBull=FALSE;
						break;
						return;
					}
				}
			}
			else if(typeid(*CUR)==typeid(CEnemy_Tank))
			{
				if(typeid(*AllObj[i])==typeid(CPlayer_Tank )||typeid(*AllObj[i])==typeid(CConcrete)||typeid(*AllObj[i])==typeid(CBrick))
				{
					if(AllObj[i]->iX<CUR->Bull->iX+CUR->Bull->iWIDTH&&AllObj[i]->iX+AllObj[i]->iWIDTH>CUR->Bull->iX&&AllObj[i]->iY<CUR->Bull->iY+CUR->Bull->iHEIGHT&&AllObj[i]->iY+AllObj[i]->iHEIGHT>CUR->Bull->iY)
					{
						if(typeid(*AllObj[i])==typeid(CPlayer_Tank ))
						{
							AllObj[i]->iArmor-=10;
							if(AllObj[i]->iArmor>0)
							{
								AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
							}
							else
							{
								delete AllObj[i];
								itrAll=AllObj.begin();									
								AllObj.erase(itrAll+i);
								AllObj.push_back(new CExplosion_Big(CUR->Bull->iX-32,CUR->Bull->iY-32,hMAIN,MAIN,BUF));
								PLAYER=false;
								GAME_OVER();
							}
						}
						else if(typeid(*AllObj[i])==typeid(CConcrete))
						{
 							AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
						}
						else if(typeid(*AllObj[i])==typeid(CBrick))
						{
							delete AllObj[i];
							itrAll=AllObj.begin();									
							AllObj.erase(itrAll+i);
							AllObj.push_back(new CExplosion_Small(CUR->Bull->iX-16,CUR->Bull->iY-16,hMAIN,MAIN,BUF));
						}
						delete CUR->Bull;
						CUR->Bull=NULL;
						CUR->bBull=FALSE;
						break;
						return;
					}
				}
			}
	}
}
bool CLevel::Menu()
{
	do
	{
		if(GetAsyncKeyState(VK_UP))
			user=0;
		if(GetAsyncKeyState(VK_DOWN))
			user=1;
		DrawTransparentBitmap(BUF,hBmp[user],70,100,mask_color);
		BitBlt(MAIN,0,0,425,445,BUF,0,0,SRCCOPY);//Вывод буфера на экран
		PatBlt(BUF,0,0,425,445,BLACKNESS);		 //Очистка экрана
	}
	while(!GetAsyncKeyState(VK_RETURN));
	if(user==1)
		return false;
	level=1;
	LOADLEVEL(level);
	return true;
}
void CLevel::LOADLEVEL(int lvl)
{
	for(int i=0;i<AllObj.size();i++)
		delete AllObj[i];
	AllObj.clear();
	Enemy_Size=0;
	if(lvl==1)
	{
		int field[26][26]={
		7,0,7,0,7,0,7,0,7,0,7,0,7,0,8,0,8,0,8,0,9,0,9,0,9,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,0,1,0,1,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,
		4,4,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,0,1,0,1,0,1,0,0,0,0,0,0,0,4,4,0,0,4,4,4,4,4,4,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,4,4,4,4,4,4,0,
		1,0,1,0,1,0,1,0,4,4,4,4,0,0,4,4,0,0,4,4,0,0,0,4,0,0,
		0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,4,4,0,0,0,4,0,0,
		1,0,1,0,1,0,1,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,0,0,
		0,0,1,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,1,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,
		0,0,4,4,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		4,4,4,0,0,4,4,4,4,0,0,4,4,4,4,4,4,4,1,0,1,0,1,0,1,0,
		4,4,4,0,0,4,4,4,4,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,1,0,1,0,1,0,1,0,
		0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,4,4,4,0,0,0,0,0,0,0,0,
		4,4,0,0,0,0,3,0,0,0,0,0,0,0,4,4,4,4,1,0,1,0,1,0,0,0,
		4,4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		4,4,4,4,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,
		4,4,4,4,0,0,3,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,
		3,3,4,4,4,4,0,0,0,0,0,4,6,0,4,0,0,0,4,4,0,0,0,0,0,0,
		3,3,4,4,4,4,0,0,0,0,0,4,0,0,4,0,0,0,4,4,0,0,0,0,0,0	};
			for(int x=0;x<26;x++)
		{
			for(int y=0;y<26;y++)
			{
				switch(field[y][x])
				{
					case 3:
						AllObj.push_back(new CConcrete(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 4:
						AllObj.push_back(new CBrick(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 6:
						AllObj.push_back(new CPlayer_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						PLAYER=true;
						break;
					case 7:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						Enemy_Size++;
						break;
					case 8:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						Enemy_Size++;
						break;
					case 9:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						Enemy_Size++;
						break;
				}
			}
		}
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==1)
					AllObj.push_back(new CGrass(x*16,y*16,hMAIN,MAIN,BUF));
	}
	if(lvl==2)
	{
			int field[26][26]={
		8,0,9,0,7,0,7,0,7,0,7,0,7,0,8,0,8,0,8,0,9,0,0,0,9,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,4,4,0,0,0,4,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,4,0,
		0,0,0,0,0,0,0,0,1,0,3,3,4,4,1,0,0,0,4,4,0,0,4,4,4,0,
		0,0,0,0,0,0,0,0,0,0,3,3,4,4,0,0,0,0,4,4,0,0,4,4,0,0,
		0,0,0,0,0,0,0,0,3,3,0,0,4,4,3,3,4,4,4,4,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,3,3,0,0,4,4,3,3,4,4,4,4,0,0,0,0,0,0,
		0,0,0,0,4,4,4,4,3,3,4,4,0,0,3,3,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,4,4,4,4,3,3,4,4,0,0,3,3,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,4,4,0,0,1,0,4,4,3,3,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,4,4,0,0,0,0,4,4,3,3,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,3,3,3,3,1,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,3,3,3,3,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,
		3,3,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,4,4,4,4,4,0,0,0,0,
		1,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,4,4,4,4,4,0,0,0,0,
		0,0,3,3,3,3,3,3,0,0,0,4,4,4,4,0,0,4,4,4,4,4,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,4,6,0,4,0,0,0,4,4,4,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,0,0,0,0,0,0,0,0,0,0,0
			};
		for(int x=0;x<26;x++)
		{
			for(int y=0;y<26;y++)
			{
				switch(field[y][x])
				{
					case 3:
						AllObj.push_back(new CConcrete(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 4:
						AllObj.push_back(new CBrick(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 6:
						AllObj.push_back(new CPlayer_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						PLAYER=true;
						break;
					case 7:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						Enemy_Size++;
						break;
					case 8:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						Enemy_Size++;
						break;
					case 9:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						Enemy_Size++;
						break;
				}
			}
		}
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==1)
					AllObj.push_back(new CGrass(x*16,y*16,hMAIN,MAIN,BUF));
	}
	if(lvl==3)
	{
			int field[26][26]={
		8,0, 9,0, 8,0, 9,0, 8,0, 9,0, 7,0, 8,0, 8,0, 8,0, 9,0, 0,0, 9,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 1,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 4,4, 4,4, 4,4, 0,0, 0,0, 0,0, 4,4, 0,0, 4,4, 1,0, 0,0,
		0,0, 0,4, 4,4, 4,4, 4,4, 0,0, 0,0, 0,0, 4,4, 0,0, 4,4, 0,0, 0,0,

		0,0, 3,3, 3,3, 0,0, 0,0, 4,4, 0,0, 4,4, 0,0, 0,0, 2,0, 1,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 4,4, 0,0, 4,4, 0,0, 0,0, 0,0, 0,0, 0,0,

		2,0, 2,0, 2,0, 0,0, 0,0, 3,3, 0,0, 4,4, 0,0, 0,0, 2,0, 2,0, 1,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 4,4, 0,0, 4,4, 0,0, 0,0, 0,0, 0,0, 0,0,

		2,0, 4,4, 4,4, 0,0, 0,0, 0,0, 0,0, 4,4, 4,4, 0,0, 0,0, 1,0, 1,0,
		0,0, 4,4, 4,4, 0,0, 0,0, 0,0, 0,0, 4,4, 4,0, 0,0, 0,0, 0,0, 0,0,

		4,4, 4,4, 4,4, 0,0, 0,0, 0,0, 0,0, 4,4, 4,0, 0,0, 0,0, 2,0, 2,0,
		4,4, 4,4, 4,4, 0,0, 0,0, 0,0, 0,0, 4,4, 0,0, 0,0, 0,0, 0,0, 0,0,

		1,0, 2,0, 2,0, 1,0, 1,0, 1,0, 1,0, 1,0, 2,0, 2,0, 1,0, 2,0, 1,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 1,0, 1,0, 0,0, 0,0, 0,0, 0,0, 0,0, 1,0, 1,0, 0,0, 1,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 4,4, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0,

		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 6,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 0,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0
			};
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==2)
					AllObj.push_back(new CWater(x*16,y*16,hMAIN,MAIN,BUF));

			for(int x=0;x<26;x++)
		{
			for(int y=0;y<26;y++)
			{
				switch(field[y][x])
				{
					case 3:
						AllObj.push_back(new CConcrete(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 4:
						AllObj.push_back(new CBrick(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 6:
						AllObj.push_back(new CPlayer_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						PLAYER=true;
						break;
					case 7:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						Enemy_Size++;
						break;
					case 8:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						Enemy_Size++;
						break;
					case 9:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						Enemy_Size++;
						break;
				}
			}
		}
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==1)
					AllObj.push_back(new CGrass(x*16,y*16,hMAIN,MAIN,BUF));
	}
	if(lvl==4)
	{
		int field[26][26]={
		8,0, 9,0, 8,0, 8,0, 9,0, 9,0, 8,0, 9,0, 8,0, 9,0, 8,0, 8,0, 8,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 3,3, 3,3, 3,3, 3,3, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0,
		0,0, 0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0,
                                                                   
		0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 1,0, 0,0, 3,3, 3,3, 3,3, 0,0, 0,0,
		0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 1,0, 3,3, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0,
                                                                   
		0,0, 3,3, 0,0, 0,0, 1,0, 3,3, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0,
		0,0, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0,
                                                                   
		0,0, 0,3, 0,0, 1,0, 3,3, 3,3, 3,3, 0,0, 3,3, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,3, 0,0, 0,0, 3,3, 3,0, 3,3, 0,0, 3,3, 0,0, 0,0, 0,0, 0,0,
                                                                   
		3,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0,
		3,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 3,3, 3,3, 3,3, 1,0, 0,0, 0,3, 0,0,
		0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 3,3, 3,3, 3,3, 0,0, 0,0, 0,3, 0,0,
                                                                   
		0,0, 0,3, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 1,0, 0,0, 0,0, 3,3, 0,0,
		0,0, 0,3, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0, 0,0, 0,0, 3,3, 0,0,
                                                                   
		0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 3,3, 1,0, 0,0, 0,0, 3,3, 3,3, 0,0,
		0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0, 0,0, 3,3, 3,3, 0,0,
                                                                   
		0,0, 3,3, 3,3, 3,3, 0,0, 0,0, 1,0, 0,0, 0,0, 3,3, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 3,3, 0,0, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 3,3, 0,0, 0,0, 3,3,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 4,4, 4,0, 0,0, 0,0, 0,0, 3,3, 3,3,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 6,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		3,3, 3,3, 0,0, 0,0, 0,0, 0,4, 0,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0};
		for(int x=0;x<26;x++)
		{
			for(int y=0;y<26;y++)
			{
				switch(field[y][x])
				{
					case 3:
						AllObj.push_back(new CConcrete(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 4:
						AllObj.push_back(new CBrick(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 6:
						AllObj.push_back(new CPlayer_Tank(x*16,y*16,hMAIN,MAIN,BUF,4));
						PLAYER=true;
						break;
					case 7:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						Enemy_Size++;
						break;
					case 8:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						Enemy_Size++;
						break;
					case 9:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						Enemy_Size++;
						break;
				}
			}
		}
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==1)
					AllObj.push_back(new CGrass(x*16,y*16,hMAIN,MAIN,BUF));
	}
	if(lvl==5)
	{
		int field[26][26]={
		8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0, 8,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 4,4, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0,
                                                                   
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 6,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0,
		0,0, 0,0, 0,0, 0,0, 0,0, 0,4, 0,0, 4,0, 0,0, 0,0, 0,0, 0,0, 0,0};
		for(int x=0;x<26;x++)
			for(int y=0;y<26;y++)
				if(field[y][x]==5)
					AllObj.push_back(new CIce(x*16,y*16,hMAIN,MAIN,BUF));
		for(int x=0;x<26;x++)
		{
			for(int y=0;y<26;y++)
			{
				switch(field[y][x])
				{
					case 3:
						AllObj.push_back(new CConcrete(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 4:
						AllObj.push_back(new CBrick(x*16,y*16,hMAIN,MAIN,BUF));
						break;
					case 6:
						AllObj.push_back(new CPlayer_Tank(x*16,y*16,hMAIN,MAIN,BUF,4));
						PLAYER=true;
						break;
					case 7:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,1));
						Enemy_Size++;
						break;
					case 8:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,2));
						Enemy_Size++;
						break;
					case 9:
						AllObj.push_back(new CEnemy_Tank(x*16,y*16,hMAIN,MAIN,BUF,3));
						Enemy_Size++;
						break;
				}
			}
		}
	}
}
void CLevel::Load_WINNER()
{
	do
	{
		if(GetAsyncKeyState(VK_ESCAPE))
			PostQuitMessage(0);
		if(GetTickCount()%2==0)
			DrawTransparentBitmap(BUF,hBmp[4],70,100,mask_color);
		else
			DrawTransparentBitmap(BUF,hBmp[5],70,100,mask_color);
		BitBlt(MAIN,0,0,425,445,BUF,0,0,SRCCOPY);//Вывод буфера на экран
		PatBlt(BUF,0,0,425,445,BLACKNESS);		 //Очистка экрана
	}
	while(!GetAsyncKeyState(VK_ESCAPE));
	PostQuitMessage(0);
}
void CLevel::GAME_OVER()
{
	do
	{
		if(GetAsyncKeyState(VK_ESCAPE))
			PostQuitMessage(0);
		DrawTransparentBitmap(BUF,hBmp[3],100,100,mask_color);
		BitBlt(MAIN,0,0,425,445,BUF,0,0,SRCCOPY);//Вывод буфера на экран
		PatBlt(BUF,0,0,425,445,BLACKNESS);		 //Очистка экрана
	}
	while(!GetAsyncKeyState(VK_ESCAPE));
	PostQuitMessage(0);
}
CGrass::~CGrass()
{
	DeleteObject(hBmp);
}
CBrick::~CBrick()
{
	DeleteObject(hBmp);
}
CWater::~CWater()
{
	DeleteObject(hBmp);
}
CConcrete::~CConcrete()
{
	DeleteObject(hBmp);
}
CIce::~CIce()
{
	DeleteObject(hBmp);
}
CExplosion_Small::~CExplosion_Small()
{
	for(int i=0;i<3;i++)
		DeleteObject(hBmp[i]);
}
CExplosion_Big::~CExplosion_Big()
{
	for(int i=0;i<6;i++)
		DeleteObject(hBmp[i]);
}
CBullet::~CBullet()
{
	for(int i=0;i<4;i++)
		DeleteObject(hBmp[i]);
}
CPlayer_Tank::~CPlayer_Tank()
{
	for(int i=0;i<8;i++)
		DeleteObject(hBmp[i]);
}
CEnemy_Tank::~CEnemy_Tank()
{
	for(int i=0;i<8;i++)
		DeleteObject(hBmp[i]);
}