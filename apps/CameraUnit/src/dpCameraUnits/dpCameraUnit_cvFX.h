//
//  dpCameraUnit_cvFX.h
//  dpHakoniwa_cameraUnit
//
//  Created by Ovis aries on 2014/12/19.
//
//

#ifndef __dpHakoniwa_cameraUnit__dpCameraUnit_cvFX__
#define __dpHakoniwa_cameraUnit__dpCameraUnit_cvFX__

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxUI.h"

class dpCameraUnit_cvFX{
public:
	dpCameraUnit_cvFX();
	~dpCameraUnit_cvFX();

	void update(ofImage &pix,bool NewFrame);

	void draw(int x,int y);
	void drawUI(int x,int y);
	void drawThumbnail(int x,int y,float scale = 1.0);

	void savePreset(string hakoniwaName);
	void loadPreset(string hakoniwaName);

	bool mEnableBlur;
	bool mEnableCanny;
	bool mEnableThreshold;
	bool mEnableAdaptiveThreshold;
	bool mEnableInvert;
	bool mEnableFrameDiff;
	bool mEnableAccumlateWeight;
	bool mEnableBackground;
	bool mEnableRunningBackground;
	bool mEnableWarpPerspective;
	bool mEnableErode1;
	bool mEnableDilate;
	bool mEnableErode;

	int mParam_Dilate_num;
	int mParam_Erode_num1;
	int mParam_Erode_num;
	float mParam_Blur;
	float mParam_Canny_Thr1;
	float mParam_Canny_Thr2;
	float mParam_Threshold;

	float mParam_accum_Time;
	int   mParam_adpThreshold_blockSize;
	int   mParam_adpThreshold_offset;
	bool  mParam_adpThreshold_invert;
	bool  mParam_adpThreshold_gauss;

	float mParam_RB_LearnTime;
	float mParam_RB_Threshold;

	ofxUICanvas mGui;
	ofImage		mSource;
	ofImage		mSourceTmp;
	ofImage		mGraySource_background;
	bool		mBackgroundNeedsReflesh;
	ofImage		mGraySource;
	ofImage		mGraySource_tmp;
	ofImage		mGraySource_forDiff;

	bool		mResetWarpPt;
	ofVec2f		mUnwarpPts[4];

protected:

	ofxCv::Mat	tmp;
	cv::Mat		mAccum;
	ofxCv::RunningBackground backGround;

	ofVec2f mLastDrawPos;
	float	mLastDrawScale;
	int mWarpTarget;
	void mousePressed(ofMouseEventArgs &arg);
	void mouseDragged(ofMouseEventArgs &arg);
	void mouseReleased(ofMouseEventArgs &arg);

	void useAccumulateWeighted(ofImage *src,ofImage *result,cv::Mat *accum,float time,bool fadeLastFrame = false);
	void useAdaptiveThreshold(ofImage &src,ofImage &dst,int blockSize,int offset,bool invert,bool gauss);
};

#endif /* defined(__dpHakoniwa_cameraUnit__dpCameraUnit_cvFX__) */
