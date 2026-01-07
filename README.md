# lvgl_android_port
[WIP] My LVGL 7 lvgldemo Android port, currently without touch input  

## copyPixelsFromBuffer
* https://github.com/devolonter/Pretty-Painter/blob/master/src/org/sprite2d/apps/pp/PainterThread.java

## https://github.com/ironsteel/ogre-android-demo

## https://github.com/hanxinhao000/DosBoxAndroid  

## Bug for Android 14 emulator
```
requestFocus();

//-------------------
//FIXME:added
//<item name="android:background">#00000</item>
//https://stackoverflow.com/questions/21311573/surfaceview-shows-black-screen-android
this.setBackgroundColor(0x00000000);
//https://stackoverflow.com/questions/3818284/android-surfaceholder-unlockcanvasandpost-does-not-cause-redraw
this.setZOrderOnTop(true);
//this.setAlpha(1.0f);
//-------------------


private void repaint() {
	if (false) {
		invalidate(); //FIXME:test this if not shown.
		// solved, use setZOrderOnTop
	} else {
		Canvas canvas = null;
		SurfaceHolder surfaceHolder = getHolder();
		try {
			if (!surfaceHolder.getSurface().isValid())
				return;
				

```

