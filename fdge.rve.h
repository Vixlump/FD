#pragma once

struct rve_item {
	string item_id;
	string item_value;
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
};
struct rve_clickbox {
	int x1;
	int y1;
	int x2;
	int y2;
	string item_name;
	string item_value;
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
					cout << "rve_items:" << rve_items[rve_cnt2].item_id << ";" << rve_items[rve_cnt2].item_value << endl;
				}
				rve_cnt2 += 1;
			}
		}
		rve_cnt += 1;
	}
}
bool fdge_rve_over_box() { return false; }
void fdge_rve_item() {}
void fdge_rve_case() {}
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
			rve_cnt += 1; input_case.name = rve_lines[rve_cnt];
			rve_cnt += 1; input_case.equto = rve_lines[rve_cnt];
			rve_cnt += 1; input_case.result = rve_lines[rve_cnt];
			rve_case.push_back(input_case);
		} else if (rve_lines[rve_cnt] == "save:") {

		} else if (rve_lines[rve_cnt] == "load:") {

		} else if (rve_lines[rve_cnt] == "quit:") {
			ofExit();
		} else if (rve_lines[rve_cnt] == "button_box:") {

		} else if (rve_lines[rve_cnt] == "text:") {

		} else if (rve_lines[rve_cnt] == "position:") {

		} else if (rve_lines[rve_cnt] == "rotate:") {

		} else if (rve_lines[rve_cnt] == "scale:") {

		} else if (rve_lines[rve_cnt] == "scene:") {

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
}
void fdge_rve_save() {}
void fdge_rve_load() {}
void fdge_rve_draw() {}