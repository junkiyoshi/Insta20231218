#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetCircleResolution(30);

	float span = 40;
	for (float x = span * 1.5; x <= ofGetWidth() - span + 1.5; x += span) {

		for (float y = span * 1.5; y <= ofGetHeight() - span * 1.5; y += span) {

			this->location_list.push_back(glm::vec2(x, y));
			this->deg_list.push_back(0);
			this->param_list.push_back(0);
		}
	}
}


//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 14;
	for (int i = 0; i < this->location_list.size(); i++) {

		this->param_list[i] = (this->param_list[i] + 12) % 360;

		if (this->param_list[i] == 0) {

			this->deg_list[i] = ofMap(ofNoise(glm::vec3(this->location_list[i] * 0.002, ofGetFrameNum() * 0.05)), 0, 1, 0, 360);
		}

		vector<glm::vec2> vertices;
		if (this->param_list[i] > 0 && this->param_list[i] < 180) {

			for (int deg = 0; deg < this->param_list[i]; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			for (int deg = 360 - this->param_list[i]; deg < 360; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}
		}

		if (this->param_list[i] >= 180 && this->param_list[i] < 360) {

			auto tmp_param = this->param_list[i] - 180;
			for (int deg = tmp_param; deg < 180; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			for (int deg = 180; deg < 360 - tmp_param; deg += 1) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}
		}

		ofPushMatrix();
		ofTranslate(this->location_list[i]);
		ofRotate(this->deg_list[i]);

		ofSetColor(239);
		ofDrawCircle(glm::vec2(), 16);
		
		ofSetColor(200, 78, 28);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}

	/*
	int start = 60 + 44;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}