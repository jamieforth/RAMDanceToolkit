#pragma once

#include "ramActorManager.h"
#include "ramActor.h"
//#include "ofxXmlSettings.h"

#pragma mark - ramBuffer

class ramSession
{
public:

	enum EntityType
	{
		RAM_UNDEFINED_TYPE = -1,
		RAM_ACTOR,
		RAM_RIGID_BODY
	};
	
	ramSession() : sessionType(RAM_UNDEFINED_TYPE), loop(true), recording(false), playing(false), rate(1.0) {}
	~ramSession() {}
	
	void clear()
	{
		actors.clear();
		rigids.clear();
		
		playhead = 0;
		duration = 0;
		frame_time = 0;
		play_start_time = 0;
		rec_start_time = 0;
		
		frame_index = 0;
		num_frames = 0;
	}
	
	int getFrame()
	{
		return floor(playhead / frame_time);
	}
	
	void setup(const string mame, int type )
	{
		clear();
		sessionName = mame;
		sessionType = type;
	}
	
	void update()
	{
		if (isRecording())
		{
			if (sessionType == RAM_ACTOR)
				appendFrame( getActorManager().getActor(sessionName) );
			
			else if (sessionType == RAM_RIGID_BODY)
				appendFrame( getActorManager().getRigidBody(sessionName) );
		}
		
		if (isPlaying())
		{
			playhead = (ofGetElapsedTimef() - play_start_time) * rate;
			frame_index = getFrame();
			
			if(frame_index >= num_frames)
			{
				frame_index = 0;
				
				if (loop)
					play_start_time = ofGetElapsedTimef();
				else
					playing = false;
			}
		}
	}

	void startRecording()
	{
		if (sessionName.empty()) return;
		
		clear();
		playing = false;
		recording = true;
		rec_start_time = ofGetElapsedTimef();
	}
	
	void stopRecording()
	{
		recording = false;
		
		duration = ofGetElapsedTimef() - rec_start_time;
		num_frames = sessionType==RAM_ACTOR ? actors.size() : sessionType==RAM_RIGID_BODY ? rigids.size() : RAM_UNDEFINED_TYPE;
		frame_time = duration / num_frames;
	}
	
	void play()
	{
		if (num_frames <= 0) return;
		
		recording = false;
		playing = true;
		play_start_time = ofGetElapsedTimef();
	}
	
	void stop()
	{
		playing = false;
	}

	void appendFrame(ramActor& actor)
	{
		if (!actor.getName().empty())
			actors.push_back(actor);
	}
	
	void appendFrame(ramRigidBody& rigid)
	{
		if (!rigid.getName().empty())
			rigids.push_back(rigid);
	}
	
	void load(const string path)
	{
		
	}
	
	void save(const string path)
	{
		
	}

	inline void setLoop(bool l) {loop = l;};
	inline void setRate(const float r) {rate = r;};
	inline void setPlayhead(const float t){playhead = t;};
	
	inline bool isPlaying() {return playing;}
	inline bool isRecording() {return recording;}
	inline bool isLoop() {return loop;}
	inline float getDuration() {return duration;}
	inline float getPlayhead() {return playhead;}
	inline string getSessionName() {return sessionName;}
	
	inline ramActor& getNextFrameActor() {return actors.at(frame_index);}
	inline ramRigidBody& getNextFrameRigid() {return rigids.at(frame_index);}
	
protected:
	
	vector<ramActor> actors;
	vector<ramRigidBody> rigids;
	
	string sessionName;
	int sessionType;
	bool loop;
	float rate;
	
	bool recording;
	bool playing;
	
	float playhead;
	float duration;
	float frame_time;
	float play_start_time;
	float rec_start_time;
	
	int frame_index;
	int num_frames;
	inline ramActorManager& getActorManager() { return ramActorManager::instance(); }
};
