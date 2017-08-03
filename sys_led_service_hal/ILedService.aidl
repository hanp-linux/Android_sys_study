package android.os;

/* 用来生成ILedService.java接口文件的 */
/** {@hide} */
interface ILedService
{
	void ledCtrl(int which, int status);
}
