#pragma once
#include "ClientDef.h"
#include  <algorithm>
#include "Socket/YTSocketConnector.h"

class GameSocket : public YTSvrLib::ITCPCONNECTOR, public YTSvrLib::CRecycle
{
	__time32_t m_tIdleExpired;	
public:
	GameSocket()
	{
		m_sendBuf.SetQueueLenMax( 1024 );
	}
    virtual void Init();

public:
	virtual int		OnSocketRecv();
    virtual int     OnRecved( const char* pBuf, int nLen );
    virtual void    OnDisconnect();
	virtual void	OnClosed();

    virtual void    PostMsg( const char* pBuf, int nLen );

    virtual void    PostDisconnectMsg( EType eType );    

    virtual void    Send( const char* buf, int nLen );
    virtual void    Send( const std::string& strPkg );  
    virtual void    Send( const std::string* pStrPkg );    
	virtual void    ReclaimObj();

	void	SetClientID( UINT nID ) { m_nClientID = nID; }
	UINT	GetClientID() { return m_nClientID; }

	void	OnRecvNewMsg(UINT nMsgSeqno,UINT nMsgType);
	void	OnSendMsg(UINT nMsgSeqno,UINT nMsgType);
private:
	UINT m_nClientID;
	MessageRecord m_mapMessageRecved;
	BOOL m_bClientClosed;
};