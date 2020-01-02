#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face_mesh.clear();
	this->frame_mesh.clear();

	int deg_span = 4;
	for(int radius = 150; radius <= 300; radius += 50){

		for (int deg = 0; deg < 360; deg += deg_span) {

			auto noise_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto param_start = 90;
			auto param_end = ofMap(ofNoise(noise_location.x * 0.008, noise_location.y * 0.008, ofGetFrameNum() * 0.005), 0, 1, 0, 180);
			int index_start = this->frame_mesh.getNumVertices();
			if (param_end > 90) {

				for (int param = param_start; param < param_end; param++) {

					int index = this->face_mesh.getNumVertices();
					vector<glm::vec3> vertices;

					vertices.push_back(glm::vec3(
						radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * cos(param * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD) * sin((param + 1) * DEG_TO_RAD),
						radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD) * sin((param + 1) * DEG_TO_RAD),
						radius * cos((param + 1) * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * cos(param * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD) * sin((param + 1) * DEG_TO_RAD),
						radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD) * sin((param + 1) * DEG_TO_RAD),
						radius * cos((param + 1) * DEG_TO_RAD)));

					this->face_mesh.addVertices(vertices);
					this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 3);
					this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

					this->frame_mesh.addVertices(vertices);
					this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
					this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
				}
			}
			else {

				for (int param = param_start; param > param_end; param--) {

					int index = this->face_mesh.getNumVertices();
					vector<glm::vec3> vertices;

					vertices.push_back(glm::vec3(
						radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * cos(param * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD) * sin((param - 1) * DEG_TO_RAD),
						radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD) * sin((param - 1) * DEG_TO_RAD),
						radius * cos((param - 1) * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD) * sin(param * DEG_TO_RAD),
						radius * cos(param * DEG_TO_RAD)));

					vertices.push_back(glm::vec3(
						radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD) * sin((param - 1) * DEG_TO_RAD),
						radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD) * sin((param - 1) * DEG_TO_RAD),
						radius * cos((param - 1) * DEG_TO_RAD)));

					this->face_mesh.addVertices(vertices);
					this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 3);
					this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

					this->frame_mesh.addVertices(vertices);
					this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
					this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
				}
			}

			if (index_start != this->frame_mesh.getNumVertices()) {

				this->frame_mesh.addIndex(index_start + 0); this->frame_mesh.addIndex(index_start + 2);
				this->frame_mesh.addIndex(this->frame_mesh.getNumVertices() - 1); this->frame_mesh.addIndex(this->frame_mesh.getNumVertices() - 3);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(300);
	
	ofSetColor(39);
	this->face_mesh.drawFaces();

	ofSetColor(239);
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}