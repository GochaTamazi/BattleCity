#include"Lib.h"
void DrawTransparentBitmap(HDC hdc,HBITMAP hBitmap,short xStart,short yStart,COLORREF cTransparentColor);

class CDlgUserClass
{
	static CDlgUserClass *ptr;
public:
	CDlgUserClass();
	static LRESULT CALLBACK WndProc(HWND hwnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	void Cls_OnDestroy(HWND hwnd);
};

class CLevel;

class CObject
{
protected:
	INT iX,iY,iWIDTH,iHEIGHT,iDir,iSpeed;
	INT iX_Old,iY_Old;
	HWND hMAIN;
	HDC MAIN,BUF;
	CObject *Bull;
	BOOL bBull;
	INT iArmor;
	INT iTIMER;
public:
	friend class CLevel;
	CObject(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show(HBITMAP hBmp);
	virtual void Show();
	virtual void Move();
	virtual ~CObject()=0;
};

class CGrass:public CObject
{
	HBITMAP hBmp;
public:
	friend class CLevel;
	CGrass(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CGrass();
};

class CBrick:public CObject
{
	HBITMAP hBmp;
public:
	friend class CLevel;
	CBrick(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CBrick();
};

class CWater:public CObject
{
	HBITMAP hBmp[2];
public:
	friend class CLevel;
	CWater(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CWater();
};

class CConcrete:public CObject
{
	HBITMAP hBmp;
public:
	friend class CLevel;
	CConcrete(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CConcrete();
};

class CIce:public CObject
{
	HBITMAP hBmp;
public:
	friend class CLevel;
	CIce(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CIce();
};

class CExplosion_Small:public CObject
{
	HBITMAP hBmp[3];
public:
	friend class CLevel;
	CExplosion_Small(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CExplosion_Small();
};

class CExplosion_Big:public CObject
{
	HBITMAP hBmp[6];
public:
	friend class CLevel;
	CExplosion_Big(INT x,INT y,HWND hmain,HDC main,HDC buf);
	void Show();
	~CExplosion_Big();
};

class CBullet:public CObject
{
	HBITMAP hBmp[4];
public:
	friend class CLevel;
	CBullet(INT x,INT y,HWND hmain,HDC main,HDC buf,INT ispeed,INT idir);
	void Move();
	void Show();
	~CBullet();
};

class CPlayer_Tank:public CObject
{
	HBITMAP hBmp[8],hCurBmp;
public:
	friend class CLevel;
	CPlayer_Tank(INT x,INT y,HWND hmain,HDC main,HDC buf,int type);
	void Move();
	void Show();
	~CPlayer_Tank();
};

class CEnemy_Tank:public CObject
{
	INT iTIMER_BEGIN,iTIMER_END,iType;
	HBITMAP hBmp[8],hCurBmp;
public:
	friend class CLevel;
	CEnemy_Tank(INT x,INT y,HWND hmain,HDC main,HDC buf,INT Type);
	void Move();
	void Show();
	~CEnemy_Tank();
};

class CLevel
{
	vector<CObject*>AllObj;
	vector<CObject*>::iterator itrAll;
	static CLevel *ptr;
	HWND hMAIN;
	HDC MAIN,BUF;
	HBITMAP hBUFFER;
	HBITMAP hBmp[6];
	int user;
	int Enemy_Size;
	bool PLAYER;
	int timer;
	int level;
public:
	CLevel(HWND hwnd);
	~CLevel();
	void Clear();
	void Action();
	static void CALLBACK TimerProc(HWND hwnd,UINT msg,UINT_PTR idEvent,DWORD dwTimer);
	void Check_Move(CObject *CUR);
	void Check_Bul(CObject *CUR);
	bool Menu();
	void LOADLEVEL(int lvl);
	void Load_WINNER();
	void GAME_OVER();
};