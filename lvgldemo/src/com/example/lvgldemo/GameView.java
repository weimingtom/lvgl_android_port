package com.example.lvgldemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameView extends SurfaceView implements Runnable {
	private final static boolean D = false;
	private final static String TAG = "GameView";

	private static final int PAUSE = 0;
    private static final int READY = 1;
	private int mode = READY;
	
	private boolean isInit = false;

	private int bgcolor = Color.BLACK;//0xFFCCCCCC;//Color.WHITE; //Color.BLACK; //0xFFCCCCCC;
	private Paint textPaintLoading;
	private Bitmap bitmap;
	private Paint mPaint;
	private Rect bounds;
	private Rect destBounds;
	
	private final static int TIMER_DELAY = 1000;
	private final static int TIMER_SLEEP_DELAY = 1000 / 24;
	private long lastTimer;
    private TimerHandler mTimerHandler = new TimerHandler();
    
    private Thread thread;
    
	public static interface OnFinishListener {
		void onFinish();
	}
	
	private OnFinishListener onFinishListener;
	
	public void setOnFinishListener(OnFinishListener onFinishListener) {
		this.onFinishListener = onFinishListener;
	}
	
	public GameView(Context context) {
		super(context);
		init(context);
	}

	public GameView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init(context);
	}
	
	public GameView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init(context);
	}
	
	private void init(Context context) {
		getHolder().addCallback(new SurfaceCallback());
		setFocusable(true);
//		setFocusableInTouchMode(true);
		requestFocus();
		//used when loading, so created here
		textPaintLoading = new Paint();
		float scale = this.getResources().getDisplayMetrics().scaledDensity;
		textPaintLoading.setTextSize(18 * scale);
		textPaintLoading.setAntiAlias(true);
		textPaintLoading.setTextAlign(Paint.Align.CENTER);
		textPaintLoading.setColor(Color.RED);//Color.BLACK);
		
		this.mPaint = new Paint();
		this.mPaint.setAntiAlias(true);
		this.mPaint.setDither(true);
		this.mPaint.setFilterBitmap(true);
		this.mPaint.setStyle(Paint.Style.FILL);
		this.mPaint.setStrokeWidth(0);
		//this.mPaint.setColor(/*Color.WHITE*/0xfffddbdf); //dialog
		this.mPaint.setColor(Color.WHITE); //dialog
		//this.mPaint.setAlpha(0xa0/*0x80*/);
		this.mPaint.setAlpha(0xFF/*0x80*/);
		
		initPixel();
		updatePixel();
	}
	
	int width = 480;
	int height = 320;
	private void initPixel() {
		bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
	}
	
	private void updatePixel() {
		this.bounds = new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight());
		this.destBounds = new Rect(0, 0, (int)(bitmap.getWidth() * 1.5), (int)(bitmap.getHeight() * 1.5));
		int[] pixels = new int[width * height];
		bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
		if (false) {
			for (int i = 0; i < pixels.length; ++i) {
				//pixels[i] = 0xff0000ff;
				pixels[i] = 0xff000000;
			}
		} else {
			int[] current = LVGLDemo.getIntArray(pixels.length);
			System.arraycopy(current, 0, pixels, 0, pixels.length);
		}
		bitmap.setPixels(pixels, 0, width, 0, 0, width, height);
	}
	
	private void onSurfaceCreated() {
		this.isInit = true;
		if (thread == null) {
			thread = new Thread(this);
			thread.start();
		}
	}

	private void onSurfaceCreated2() {
		
	}
	
	private void onSurfaceChanged(int width, int height) {
		
	}
	
	@Override
	public void draw(Canvas canvas) {
		updatePixel();
		
		canvas.save();
		// background
		canvas.drawColor(bgcolor);
		if (!this.isInit) {
			//canvas.drawText("hello, world!", this.getWidth() / 2, this.getHeight() / 2, textPaintLoading);
			canvas.drawBitmap(bitmap, bounds, destBounds, mPaint);
		} else {	
			canvas.drawText("loading...", this.getWidth() / 2, this.getHeight() / 2, textPaintLoading);
		}
		canvas.restore();
	}
	
	public void onFirstStartedState() {
		if (D) {
			Log.e(TAG, "onFirstStartedState");
		}
		setMode(READY);
		onTimer();
	}
	
	public void onRestartedState() {
		if (D) {
			Log.e(TAG, "onRestartedState");
		}
		setMode(READY);
		onTimer();
	}
	
	public void onPauseState() {
		if (D) {
			Log.e(TAG, "onPauseState");
		}
		setMode(PAUSE);
	}
	
	public void onStopState() {
		if (D) {
			Log.e(TAG, "onStopState");
		}
	}
	
	@Override
	protected void onDetachedFromWindow() {
		super.onDetachedFromWindow();
		if (D) {
			Log.e(TAG, "onDetachedFromWindow");
		}
	}

	private void setMode(int newMode) {
		this.mode = newMode;
	}
	
	private void repaint() {
		Canvas canvas = null;
		SurfaceHolder surfaceHolder = getHolder();
		try {
			canvas = surfaceHolder.lockCanvas();
			if (canvas == null) {
				return;
			}
			synchronized (surfaceHolder) {
				draw(canvas);
			}
		} finally {
			if (canvas != null) {
				surfaceHolder.unlockCanvasAndPost(canvas);
			}
		}
	}
	
	private void repaint2() {
		SurfaceHolder surfaceHolder = getHolder();
		Canvas canvas = surfaceHolder.lockCanvas();
		if (canvas != null) {
			draw(canvas);
			surfaceHolder.unlockCanvasAndPost(canvas);
		}
	}
	
	@Override 
    public boolean onTouchEvent(MotionEvent e) {
		if (e == null) {
			return false;
		}
        int count = e.getPointerCount();
        boolean isRepaint = false;
        for (int i = 0; i < count; i++) {
            final float x = e.getX(i);
            final float y = e.getY(i);
            final int owner = e.getPointerId(i);
            int action = e.getAction() & MotionEvent.ACTION_MASK;
            switch (action) {
            case MotionEvent.ACTION_UP:
	        case MotionEvent.ACTION_POINTER_UP:
	        	action = MotionEvent.ACTION_UP;
	        	handleClick(x, y);
//	        	Log.e(TAG, "handleClick " + x + ", " + y);
	        	isRepaint = true;
	        	break;
	        	
	        case MotionEvent.ACTION_DOWN:
	        case MotionEvent.ACTION_POINTER_DOWN:
                action = MotionEvent.ACTION_DOWN;
                break;
                
            default:
                break;
	        }
        }
        if (isRepaint) {
        	repaint();
        }
        return true;
    } 

	private void handleClick(float x, float y) {
    	
	}
	
	private class SurfaceCallback implements SurfaceHolder.Callback {
		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
			if (D) {
				Log.e(TAG, "surfaceChanged");
			}
			onSurfaceChanged(width, height);
			//repaint();
		}

		@Override
		public void surfaceCreated(SurfaceHolder holder) {
			if (D) {
				Log.e(TAG, "surfaceCreated");
			}
			onSurfaceCreated();
			//repaint();
		}

		@Override
		public void surfaceDestroyed(SurfaceHolder holder) {
			
		}
	}
	
	private void onTimer() {
		if (isInit) {
			repaint();
			this.onSurfaceCreated2();
			isInit = false;
		}
		
		if (mode == PAUSE) {
			return;
		}
        long now = System.currentTimeMillis();
        boolean isRepaint = false;
        if (now - lastTimer > TIMER_DELAY) {
        	//repaint();
        	isRepaint = true;
        	lastTimer = now;
        }
        if (isRepaint) {
        	repaint();
        }
        long delta = System.currentTimeMillis() - now;
        if (TIMER_SLEEP_DELAY > delta) {
        	mTimerHandler.sleep(TIMER_SLEEP_DELAY - delta);
        } else {
        	mTimerHandler.sleep(0);
        }
	}
	
    private class TimerHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
        	GameView.this.onTimer();
        }
        
        public void sleep(long delayMillis) {
        	this.removeMessages(0);
            sendMessageDelayed(obtainMessage(0), delayMillis);
        }
    }

	@Override
	public void run() {
		LVGLDemo.main();
	}
}

