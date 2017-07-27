/*************************************************************************
	> File Name: LedService.java
	> Author: hanp 
	> Mail: ma6174@163.com 
	> Created Time: 2017年07月26日 星期三 16时23分18秒
 ************************************************************************/
package com.android.server;

import android.os.ILedService;


/* 调用本地native方法，操作硬件 */
public class LedService extends ILedService.Stub
	implements InputManager.InputDeviceListener {
	private static final String TAG = "LedService";

	public LedService()
	{
		native_ledOpen();
	}

	public void ledCtrl(int which, int status) throws android.os.RemoteException
	{
		return native_ledCtrl(which, status);
	}

	public  native void native_ledOpen(void);
	public  native void native_ledCtrl(int which, int status);
	public  native void native_ledClose(void);

}

