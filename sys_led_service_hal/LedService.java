/*************************************************************************
	> File Name: LedService.java
	> Author: hanp 
	> Mail: ma6174@163.com 
	> Created Time: 2017年07月26日 星期三 16时23分18秒
 ************************************************************************/
package com.android.server;

import android.os.ILedService;
import android.util.Slog;


/* 调用本地native方法，操作硬件 */
public class LedService extends ILedService.Stub
{
	private static final String TAG = "LedService";

	public LedService()
	{
		Slog.i(TAG, "public LedService()");
		native_ledOpen();
		native_ledCtrl(0, 1);
		native_ledCtrl(1, 1);
		native_ledCtrl(2, 1);
		native_ledCtrl(3, 1);
	}

	public void ledCtrl(int which, int status) throws android.os.RemoteException
	{
		Slog.i(TAG, "ledCtrl(int which = "+which+", int status = "+status+")");
		native_ledCtrl(which, status);
	}

	public  native void native_ledOpen();
	public  native void native_ledCtrl(int which, int status);
	public  native void native_ledClose();

}

