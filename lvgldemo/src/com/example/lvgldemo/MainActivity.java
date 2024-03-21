/**
 * 
 */
package com.example.lvgldemo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;

public class MainActivity extends Activity {
	private static final boolean D = false;
	private static final String TAG = "MainActivity";
	
	private GameView gameBoard;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //hideTitle();
        this.gameBoard = new GameView(this);
        FrameLayout layout = new FrameLayout(this);
        layout.addView(gameBoard);
        setContentView(layout);
        
        gameBoard.setOnFinishListener(new GameView.OnFinishListener() {
			@Override
			public void onFinish() {
				if (D) {
					Log.d(TAG, "onFinish");
				}
				finish();
			}
        });
        
		if (savedInstanceState == null) {
			onFirstStartedState();
        } else {
            boolean isFirstSaved = savedInstanceState.getBoolean("isFirstSaved");
            if (isFirstSaved) {
            	onRestartedState();
            } else {
                onPauseState(); //FIXME:
            }
        }
    }
    
	@Override
	protected void onStop() {
		super.onStop();
		onStopState();
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		onRestartedState();
	}
	
    @Override
    protected void onPause() {
        super.onPause();
        onPauseState();
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
        outState.putBoolean("isFirstSaved", true);
    }

    public void hideTitle() {
    	this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
    	this.requestWindowFeature(Window.FEATURE_NO_TITLE);
    }
    
	private void onFirstStartedState() {
		if (D) {
			Log.e(TAG, "onFirstStartedState");
		}
		if (this.gameBoard != null) {
			this.gameBoard.onFirstStartedState();
		}
	}
    
	private void onRestartedState() {
		if (D) {
			Log.e(TAG, "onRestartedState");
		}
		if (this.gameBoard != null) {
			this.gameBoard.onRestartedState();
		}
	}
	
	private void onPauseState() {
		if (D) {
			Log.e(TAG, "onPauseState");
		}
		if (this.gameBoard != null) {
			this.gameBoard.onPauseState();
		}
	}
	
	private void onStopState() {
		if (D) {
			Log.e(TAG, "onStopState");
		}
		if (this.gameBoard != null) {
			this.gameBoard.onStopState();
		}
	}

}
