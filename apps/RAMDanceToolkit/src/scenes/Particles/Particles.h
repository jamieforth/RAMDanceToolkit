// 
// Particles.h - RAMDanceToolkit
// 
// Copyright 2012-2013 YCAM InterLab, Yoshito Onishi, Satoru Higa, Motoi Shimizu, and Kyle McDonald
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//    http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "ParticleEngine.h"

class Particles : public ramBaseScene
{
	
	ParticleEngine pe;
	Gravity *gravity;
	Floor *floor;
	
	float particle_amount;
	
	ramFilterEach<ramGhost> ghostFilters;
    bool useGhost;
	
public:
	
	Particles() : particle_amount(4.0), useGhost(false) {}
	
	void setupControlPanel()
	{
        ramGetGUI().addToggle("Change emit position", &useGhost);
		ramGetGUI().addSlider("Amount", 1.0, 15.0, &particle_amount);
		ramGetGUI().addSlider("Life", 0.1, 10.0, &pe.particle_life);
		ramGetGUI().addSlider("Velocity", 0.1, 5, &pe.particle_velocity);
		ramGetGUI().addSlider("Gravity", -0.1, 0.1, &gravity->force);
	}
	
	void setup()
	{
		pe.setup(50000);
		
		gravity = new Gravity;
		floor = new Floor;
		pe.addForceFactor(gravity);
		pe.addForceFactor(floor);
	}
	
	
	void update()
	{
        
		const vector<ramNodeArray>& NAs = useGhost ? ghostFilters.update(getAllNodeArrays()) : getAllNodeArrays();
        
		for (int n = 0; n < NAs.size(); n++)
		{
			const ramNodeArray &NA = NAs[n];
			
			for (int i = 0; i < NA.getNumNode(); i++)
			{
				const ramNode &node = NA.getNode(i);
				
				for(int j=0; j<particle_amount; j++)
					pe.emit( node.getGlobalPosition() );
			}
		}
		
		pe.update();
	}
	
	void draw()
	{
		ramBeginCamera();
		
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_DEPTH_TEST);
		ofPushStyle();
		ofNoFill();

		ofSetColor(255, 30);
		pe.draw();
		
		ofPopStyle();
		glPopAttrib();
		
		ramEndCamera();
	}
	
	void loadPreset(size_t preset_id=0)
	{
		particle_amount = 5.0;
		pe.particle_life = 2.6;
		pe.particle_velocity = 0.7;
		gravity->force = -0.01;
	}
		
	string getName() const { return "Particles"; }
};
