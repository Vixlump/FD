#pragma once

struct rve_item {
	string item_id;
	string item_value;
};
struct rve_sprite {
	ofImage sprite;
	vector <int> key_x;
	vector <int> key_y;
	bool ani;
	int speed;
	int dim_x;
	int dim_y;
	int cols;
	int rows;
};
struct rve_image {
	ofImage img;
	int x;
	int y;
	int xs;
	int ys;
};
struct rve_video {
	ofVideoPlayer vid;
	int x;
	int y;
	int xs;
	int ys;
};
struct rve_itemcase {
	string name;
	string equto;
	string result;
	vector <string> action;
};
struct rve_clickbox {
	int x1;
	int y1;
	int x2;
	int y2;
	string item_name;
	string item_value;
};
struct rve_time {
	chrono::high_resolution_clock::time_point start;
	double seconds;
	string item_name;
	string new_value;
};

struct rve_3d {
	ofMesh model;
	ofVec3f pos;
	ofVec3f trans;
	ofVec3f scale;
	ofVec3f rot;
};

ifstream rve_reader;
vector <string> rve_lines;
bool rve_fullscreen = false;
unsigned short int rve_x;
unsigned short int rve_y;
rve_image rve_background_image;
short int rve_background_type;
ofSoundPlayer rve_music;
bool rve_music_starter = false;
vector <rve_image> rve_images;
vector <ofImage> rve_sprites;
bool rve_videos_starter = false;
vector <rve_video> rve_videos;
bool rve_sounds_starter = false;
vector <ofSoundPlayer> rve_sounds;
vector <rve_clickbox> rve_click_box;
vector <rve_item> rve_items;
vector <rve_itemcase> rve_case;
bool rve_scene_change = false;
string rve_scene_new = "";
ofstream rve_saver;
ifstream rve_loader;
vector <rve_time> rve_delays;
void fdge_rve_resolution() { ofSetWindowShape(rve_x, rve_y); }
void fdge_rve_fullscreen() { ofToggleFullscreen(); }

void fdge_rve_background_image() {
	rve_background_image.img.draw(rve_background_image.x, rve_background_image.y, rve_background_image.xs, rve_background_image.ys);
}
void fdge_rve_background_video() {}
void fdge_rve_background_360image() {}
void fdge_rve_background_360video() {}
void fdge_rve_music() { if (rve_music_starter == true) { rve_music.play(); rve_music_starter = false; } }
void fdge_rve_imagenvid() {
	unsigned int rve_cnt = 0;
	while (rve_cnt < rve_videos.size()) {
		rve_videos[rve_cnt].vid.draw(rve_videos[rve_cnt].x, rve_videos[rve_cnt].y, rve_videos[rve_cnt].xs, rve_videos[rve_cnt].ys);
		rve_cnt += 1;
	}
	rve_cnt = 0;
	while (rve_cnt < rve_images.size()) {
		rve_images[rve_cnt].img.draw(rve_images[rve_cnt].x, rve_images[rve_cnt].y, rve_images[rve_cnt].xs, rve_images[rve_cnt].ys);
		rve_cnt += 1;
	}
}

void fdge_rve_video_start() {
	if (rve_videos_starter == true) {
		unsigned int rve_cnt = 0;
		while (rve_cnt < rve_videos.size()) {
			rve_videos[rve_cnt].vid.play();
			rve_cnt += 1;
		}
		rve_videos_starter = false;
	}
}

void fdge_rve_video_update() {
	unsigned int rve_cnt = 0;
	while (rve_cnt < rve_videos.size()) {
		rve_videos[rve_cnt].vid.update();
		rve_cnt += 1;
	}
}

void fdge_rve_sprite() {}

void fdge_rve_sound() {
	if (rve_sounds_starter == true) {
		unsigned int rve_cnt = 0;
		while (rve_cnt < rve_sounds.size()) {
			rve_sounds[rve_cnt].play();
			rve_cnt += 1;
		}
		rve_sounds_starter = false;
	}
}
void fdge_rve_gui() {}
void fdge_rve_click_box(int x, int y) {
	unsigned int rve_cnt = 0;
	while (rve_cnt < rve_click_box.size()) {
		if ((rve_click_box[rve_cnt].x1 <= x) and (x <= rve_click_box[rve_cnt].x2) and (rve_click_box[rve_cnt].y1 <= y) and (y <= rve_click_box[rve_cnt].y2)) {
			unsigned int rve_cnt2 = 0;
			while (rve_cnt2 < rve_items.size()) {
				if (rve_items[rve_cnt2].item_id == rve_click_box[rve_cnt].item_name) {
					rve_items[rve_cnt2].item_value = rve_click_box[rve_cnt].item_value;
					//cout << "rve_items:" << rve_items[rve_cnt2].item_id << ";" << rve_items[rve_cnt2].item_value << endl;
				}
				rve_cnt2 += 1;
			}
		}
		rve_cnt += 1;
	}
}
bool fdge_rve_over_box() { return false; }
void fdge_rve_item() {}
unsigned int fdge_rve_case_check(string input_case) {
	if (input_case == "change_scene") {
		return 1;
	} else if (input_case == "edit_item") {
		return 2;
	} else if (input_case == "draw_image") {
		return 5;
	} else if (input_case == "draw_video") {
		return 6;
	} else if (input_case == "draw_sprite") {
		return 6;
	} else if (input_case == "quit") {
		return 0;
	} else if (input_case == "new_click_box") {
		return 6;
	} else if (input_case == "new_over_box") {
		return 6;
	} else if (input_case == "play_sound") {
		return 2;
	} else if (input_case == "edit_music") {
		return 2;
	} else if (input_case == "keypressed") {
		return 3;
	} else if (input_case == "edit_background") {
		return 6;
	} else {
		return 0;
	}

}

void fdge_rve_translate() {
	unsigned int rve_cnt = 0;
	while (rve_cnt < rve_lines.size()) {
		if (rve_lines[rve_cnt]=="resolution:") {
			rve_cnt += 1;
			rve_x = abs(atof(rve_lines[rve_cnt].c_str()));
			rve_cnt += 1;
			rve_y = abs(atof(rve_lines[rve_cnt].c_str()));
		} else if (rve_lines[rve_cnt] == "fullscreen:") {
			rve_fullscreen = true;
		} else if (rve_lines[rve_cnt] == "background:") {
			rve_cnt += 1;
			if (rve_lines[rve_cnt] == "sta_img") {
				rve_background_type = 0;
				rve_cnt += 1; rve_background_image.x = atof(rve_lines[rve_cnt].c_str());
				rve_cnt += 1; rve_background_image.y = atof(rve_lines[rve_cnt].c_str());
				rve_cnt += 1; rve_background_image.xs = atof(rve_lines[rve_cnt].c_str());
				rve_cnt += 1; rve_background_image.ys = atof(rve_lines[rve_cnt].c_str());
				rve_cnt += 1; rve_lines[rve_cnt] = "/content/" + rve_lines[rve_cnt]; rve_background_image.img.loadImage(rve_lines[rve_cnt]);
				rve_background_image.x -= (rve_background_image.xs / 2); rve_background_image.y -= (rve_background_image.ys / 2);
			}
		} else if (rve_lines[rve_cnt] == "image:") {
			rve_image input_image;
			rve_cnt += 1; input_image.x = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_image.y = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_image.xs = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_image.ys = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; rve_lines[rve_cnt] = "/content/" + rve_lines[rve_cnt]; input_image.img.loadImage(rve_lines[rve_cnt]);
			input_image.x -= (input_image.xs / 2); input_image.y -= (input_image.ys / 2);
			rve_images.push_back(input_image);
		} else if (rve_lines[rve_cnt] == "video:") {
			rve_video input_video;
			rve_cnt += 1; input_video.x = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_video.y = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_video.xs = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_video.ys = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; rve_lines[rve_cnt] = "/content/" + rve_lines[rve_cnt]; input_video.vid.load(rve_lines[rve_cnt]);
			input_video.x -= (input_video.xs / 2); input_video.y -= (input_video.ys / 2);
			rve_videos.push_back(input_video);
			rve_videos_starter = true;
		} else if (rve_lines[rve_cnt] == "sprite:") {

		} else if (rve_lines[rve_cnt] == "music:") {
			rve_cnt += 1;
			rve_lines[rve_cnt] = "/content/" + rve_lines[rve_cnt];
			rve_music.load(rve_lines[rve_cnt]);
			rve_cnt += 1;
			if (rve_lines[rve_cnt] == "loop") {
				rve_music.setLoop(true); rve_music_starter = true;
			} else if (rve_lines[rve_cnt] == "play") {
				rve_music.setLoop(false); rve_music_starter = true;
			}
		} else if (rve_lines[rve_cnt] == "sound:") {
			ofSoundPlayer input_sound;
			rve_cnt += 1;
			rve_lines[rve_cnt] = "/content/" + rve_lines[rve_cnt];
			input_sound.load(rve_lines[rve_cnt]);
			rve_cnt += 1;
			if (rve_lines[rve_cnt] == "loop") {
				input_sound.setLoop(true); rve_sounds_starter = true;
			} else if (rve_lines[rve_cnt] == "play") {
				input_sound.setLoop(false); rve_sounds_starter = true;
			}
			rve_sounds.push_back(input_sound);
		} else if (rve_lines[rve_cnt] == "click_box:") {
			rve_clickbox input_clickbox;
			rve_cnt += 1; input_clickbox.x1 = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_clickbox.y1 = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_clickbox.x2 = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_clickbox.y2 = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_clickbox.item_name = rve_lines[rve_cnt];
			rve_cnt += 1; input_clickbox.item_value = rve_lines[rve_cnt];
			rve_click_box.push_back(input_clickbox);
		} else if (rve_lines[rve_cnt] == "over_box:") {
			
		} else if (rve_lines[rve_cnt] == "keypressed:") {
			
		} else if (rve_lines[rve_cnt] == "gui:") {

		} else if (rve_lines[rve_cnt] == "item:") {
			rve_item input_item;
			rve_cnt += 1; input_item.item_id = rve_lines[rve_cnt];
			rve_cnt += 1; input_item.item_value = rve_lines[rve_cnt];
			rve_items.push_back(input_item);
		} else if (rve_lines[rve_cnt] == "case:") {
			rve_itemcase input_case;
			unsigned int rve_cnt2 = 0;
			unsigned int rve_max = 0;
			rve_cnt += 1; input_case.name = rve_lines[rve_cnt];
			rve_cnt += 1; input_case.equto = rve_lines[rve_cnt];
			rve_cnt += 1; input_case.result = rve_lines[rve_cnt];
			rve_max = fdge_rve_case_check(input_case.result);
			while (rve_cnt2 < rve_max) {
				rve_cnt += 1; input_case.action.push_back(rve_lines[rve_cnt]);
				rve_cnt2 += 1;
			}
			rve_case.push_back(input_case);
		} else if (rve_lines[rve_cnt] == "save:") {
			rve_cnt += 1; rve_saver.open(rve_lines[rve_cnt]);
			for (int i = 0; i < rve_items.size(); i++) { rve_saver << rve_items[i].item_id + ";" + rve_items[i].item_value; rve_saver << endl; }
			rve_saver.close();
		} else if (rve_lines[rve_cnt] == "load:") {
			rve_cnt += 1; rve_loader.open(rve_lines[rve_cnt]); 
			string input_string; vector <string> all_items; rve_items.clear();
			while (getline(rve_loader, input_string)) { all_items.push_back(input_string); }
			rve_loader.close(); vector <string> passable_items; rve_item pusher_backer;
			for (int i = 0; i < all_items.size(); i++) {
				passable_items.clear(); stringstream check_list(all_items[i]);
				while (getline(check_list, input_string, ';')) { passable_items.push_back(input_string); }
				pusher_backer.item_id = passable_items[0]; pusher_backer.item_value = passable_items[1];
				rve_items.push_back(pusher_backer);
			}
		} else if (rve_lines[rve_cnt] == "reset_save:") {

		} else if (rve_lines[rve_cnt] == "quit:") {
			ofExit();
		} else if (rve_lines[rve_cnt] == "button_box:") {

		} else if (rve_lines[rve_cnt] == "text:") {

		} else if (rve_lines[rve_cnt] == "position:") {

		} else if (rve_lines[rve_cnt] == "rotate:") {

		} else if (rve_lines[rve_cnt] == "scale:") {

		} else if (rve_lines[rve_cnt] == "3d:") {

		} else if (rve_lines[rve_cnt] == "delay:") {
			rve_time input_time;
			rve_cnt += 1; input_time.seconds = atof(rve_lines[rve_cnt].c_str());
			rve_cnt += 1; input_time.item_name = rve_lines[rve_cnt];
			rve_cnt += 1; input_time.new_value = rve_lines[rve_cnt];
			input_time.start = chrono::high_resolution_clock::now();
			rve_delays.push_back(input_time);
		} else if (rve_lines[rve_cnt] == "scene:") {
			rve_scene_change = true;
			rve_cnt += 1; rve_scene_new = "scenes/" + rve_lines[rve_cnt] + ".rve.fdge";
		} else if (rve_lines[rve_cnt] == "print:") {
			rve_cnt += 1;
			for (int i = 0; i < rve_items.size(); i++) { if (rve_items[i].item_id == rve_lines[rve_cnt]) { cout << "FDGE.RVE."<< rve_items[i].item_id<< ": " << rve_items[i].item_value << endl; break; } }
		} else if (rve_lines[rve_cnt] == "reset_items:") {
			rve_items.clear();
		}
		rve_cnt += 1;
	}
}
void fdge_rve_register(string rve_filename) {
	rve_reader.open(rve_filename);
	string rve_intermediate;
	while (getline(rve_reader, rve_intermediate)) {
		rve_lines.push_back(rve_intermediate);
	}
	rve_reader.close();
	fdge_rve_translate();
}
void fdge_rve_setup() {
	fdge_rve_register("scenes/active.rve.fdge");
}
void fdge_rve_changescene() {
	rve_lines.clear();
	rve_images.clear();
	rve_sprites.clear();
	rve_videos.clear();
	rve_sounds.clear();
	rve_click_box.clear();
	rve_case.clear();
	rve_delays.clear();
	fdge_rve_register(rve_scene_new);
	rve_scene_change = false;
}

void fdge_rve_delay() {
	if (rve_delays.empty() == false) {
		double comparitor;
		for (int i = 0; i < rve_delays.size(); i++) {
			auto time_current_test = chrono::high_resolution_clock::now();
			comparitor = chrono::duration_cast<chrono::seconds>(time_current_test - rve_delays[i].start).count();
			if (comparitor >= rve_delays[i].seconds) {
				for (int f = 0; f < rve_items.size(); f++) {
					if (rve_items[f].item_id == rve_delays[i].item_name) {
						rve_items[f].item_value = rve_delays[i].new_value; break;
					}
				}
			}
		}
	}
}
void fdge_rve_save() {}
void fdge_rve_load() {}
void fdge_rve_draw() {}

void fdge_rve_case() {
	if (rve_case.empty()==false) {
		unsigned int rve_cnt = 0;
		while (rve_cnt < rve_case.size()) {
			unsigned int rve_cnt2 = 0;
			while (rve_cnt2 < rve_items.size()) {
				if ((rve_case[rve_cnt].name==rve_items[rve_cnt2].item_id)and(rve_case[rve_cnt].equto==rve_items[rve_cnt2].item_value)) {
					if (rve_case[rve_cnt].result == "change_scene") {
						rve_scene_change = true;
						rve_scene_new = "scenes/" + rve_case[rve_cnt].action[0] + ".rve.fdge";
					} else if (rve_case[rve_cnt].result == "edit_item") {
						for (int i = 0; i < rve_items.size(); i++) {
							if (rve_items[i].item_id == rve_case[rve_cnt].action[0]) { rve_items[i].item_value = rve_case[rve_cnt].action[1]; break; }
						}
					} else if (rve_case[rve_cnt].result == "quit") {
						ofExit();
					} else if (rve_case[rve_cnt].result == "reset_items") {
						rve_items.clear();
					}
				}
				rve_cnt2 += 1;
			}
			rve_cnt += 1;
		}
	}
}
