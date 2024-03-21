package com.example.lvgldemo;

public class LVGLDemo {
	public static native int[] getIntArray(int size);
	public static native void main();
	
    static {  
        System.loadLibrary("lvgldemo");  
    }
}
