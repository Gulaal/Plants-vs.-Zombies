#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;

class FlowerImage {
public:
	string currentPicture;
	string weapon;
	int posWeaponX;
	int posWeaponY;
	string doing;
	double dx;
	bool reprinting = false;
	virtual void setModel() = 0;
	virtual void weaponFrom() = 0;
	virtual void setSpeedDx(double) = 0;
	virtual void setDoing() = 0;
	virtual void updateBullet(RenderWindow& window, double time) = 0;
};

class SunflowerImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {
		dx = a;
	}
	void setModel() {
		currentPicture = "modelПодсолнух.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

class PeaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "снарядГорошек.png";
		posWeaponX = 100;
		posWeaponY = 28;
	}

	void setSpeedDx(double speed) {
		dx = speed;
	}

	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelГорошек.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;

		Image bulletRender;
		bulletRender.loadFromFile("снарядГорошек.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		window.draw(newSprite);
	}
};

class CabbageImage : public FlowerImage {
	void weaponFrom() {
		weapon = "снарядКапуста.png";

		posWeaponX = 13;
		posWeaponY = 20;
	}
	void setSpeedDx(double speed = 0.03) {
		dx = speed;
	}
	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelКапуста.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		Image bulletRender;
		bulletRender.loadFromFile("снарядКапуста.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		newSprite.setTextureRect(IntRect(0, 0, 80, 80));
		newSprite.setPosition(posWeaponX, posWeaponY);
		window.draw(newSprite);
	}
};

class NutImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "modelОрех.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

class ActiniaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "сюрикен1.png";
		posWeaponX = 103;
		posWeaponY = 28;
	}

	void setSpeedDx(double speed = 0.03) {
		//dx = speed;
	}
	void setDoing() {
		doing = "Кушать";
	}
	void setModel() {
		currentPicture = "modelАктиния.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		Image bulletRender;
		if (posWeaponX % 2 == 0)
			bulletRender.loadFromFile("сюрикен1.png");
		else
			bulletRender.loadFromFile("сюрикен2.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		window.draw(newSprite);
	}

};

class BombImage : public FlowerImage {
	void setDoing() {
		doing = "Кушать";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "modelБомба.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

class FlowerPhysic {
public:
	int health;
	int damage;
	bool zombieInWay;
	bool isAvialiable;
	int weaponX;
	Clock timeToCooldaun;
public:
	virtual void setHealthPoint(int) = 0;
	virtual void setDamagePoint(int) = 0;
	virtual int getHealthPoint() = 0;
	virtual int getDamage() = 0;
	virtual bool needToActivate(int) = 0;

	void ripFlower() {
		isAvialiable = false;
	}

	bool isOnMap() {
		return isAvialiable;
	}

	virtual ~FlowerPhysic() {}
};

class SunflowerPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int i = 1) {
		zombieInWay = true;
		return zombieInWay;
	}
	virtual ~SunflowerPhysic() {}
};

class PeaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 20) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~PeaPhysic() {}
};

class NutPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~NutPhysic() {}
};

class CabbagePhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 30) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~CabbagePhysic() {}
};

class ActiniaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 120) {
		health = point;
	}
	void setDamagePoint(int point = 10) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~ActiniaPhysic() {}
};

class BombPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 0) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2)
	{
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~BombPhysic() {}
};

class FlowerFactory {
public:
	virtual FlowerImage* makeFlower() = 0;
	virtual FlowerPhysic* makePhysic() = 0;
};

class SunflowersFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new SunflowerImage();
	}
	FlowerPhysic* makePhysic() {
		return new SunflowerPhysic();
	}
};

class PeaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new PeaImage();
	}
	FlowerPhysic* makePhysic() {
		return new PeaPhysic();
	}
};

class CabbageFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new CabbageImage();
	}
	FlowerPhysic* makePhysic() {
		return new CabbagePhysic();
	}
};

class NutFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new NutImage();
	}
	FlowerPhysic* makePhysic() {
		return new NutPhysic();
	}
};

class ActiniaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new ActiniaImage();
	}
	FlowerPhysic* makePhysic() {
		return new ActiniaPhysic();
	}
};

class BombFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new BombImage();
	}
	FlowerPhysic* makePhysic() {
		return new BombPhysic();
	}
};

class FlowerPair
{
public:
	FlowerImage* image;
	FlowerPhysic* physic;
};

class Flower {
public:
	FlowerPair* createFlower(FlowerFactory& factory) {
		FlowerPair* p = new FlowerPair;
		p->image = factory.makeFlower();
		p->physic = factory.makePhysic();
		return p;
	}
};

class Zombie {
public:

	float dx;
	float dy;
	string fileName;
	float x;
	float y;
	Sprite sprite;
	bool statusAviliable;
	int health;
	int damage;
	bool isLive;
	bool isEaten;

	Zombie(RenderWindow &window, int posLine) {
		statusAviliable = true;
		isLive = false;
		isEaten = false;
		Image ZombieRender;
		fileName = "zombieOnPlace.png";
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		sprite.setTexture(texture);
		srand(time(0));
		x = 1100;
		y = 125 + (posLine - 1) * 110;
		dx = -0.01;
		sprite.setTextureRect(IntRect(0, 0, 140, 140));
		sprite.setPosition(x, y);
		health = 150;
		damage = 10;
	}

	void update(RenderWindow &window, float time) {
		x += dx * time;
		if (fileName.find("On") != -1)
			fileName = "zombieInRun.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		window.draw(newSprite);

	}

	double myDamage() {
		return damage;
	}
	void setUnvialible() {
		statusAviliable = false;
	}


	bool isAvialible() {
		return statusAviliable;
	}

	void getDamage(FlowerPhysic* someFlower) {
		health -= someFlower->getDamage();
		if (health <= 0)
			ripZombie();
	}

	void setDamage(FlowerPhysic* someFlower) {
		someFlower->health -= damage;
		if (someFlower->health <= 0) {
			someFlower->ripFlower();
			this->isEaten = false;
		}
	}

	void ripZombie() {
		statusAviliable = false;
	}

	bool isZombieRip() {
		return statusAviliable;
	}


	void setNextPictureEating(RenderWindow& window) {
		
		if (fileName.find("Ест") == -1)
			fileName = "ЗомбиЕст.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		
		window.draw(newSprite);
	}
};

class Car {
public:
	float dx;
	string fileName;
	float x;
	float y;
	Sprite sprite;
	bool isRunningStatus;
	Car(RenderWindow &window, int numberCar) {
		Image car;
		car.loadFromFile("modelТачка.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 120, 120));
		auto i = numberCar;
		sprite.setPosition(190, 140 + i * 110);
		x = 190;
		y = 140 + i * 110;
		dx = 0.1;
		isRunningStatus = false;
		window.draw(sprite);
	}
	void update(RenderWindow &window, float time, int num) {
		x += dx * time;

		Image car;
		car.loadFromFile("modelТачка.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 120, 120));
		sprite.setPosition(x, y);
		dx = 0;
		window.draw(sprite);
	}

	bool isRun() {
		return isRunningStatus;
	}

	void carIsRunning(RenderWindow& window, int x1, vector<Zombie> &listZombies, vector<int> zombiesInLine, double time) {
		for (auto i = 0; i < zombiesInLine.size(); i++) {
			int x2 = listZombies[zombiesInLine[i]].x;
			if ((x1 > x2) && (x1 < 1100)) {
				dx = 0.02;
				update(window, time, 0);
				listZombies[zombiesInLine[i]].isLive = false;
				listZombies[zombiesInLine[i]].health = -1;
				isRunningStatus = true;
			}
		}
	}

	void getDamage(Zombie* zombie) {
		zombie->health -= 200;
		if (zombie <= 0)
			zombie->ripZombie();
	}

};

class CarCollection {
public:
	friend class CarsIterator;
	vector<Car> items;
	int position;
	CarCollection() {
		position = -1;
	}
	void push(Car in)
	{
		items.push_back(in);
	}
	Car pop()
	{
		return items[position--];
	}
	bool isEmpty()
	{
		return (position == -1);
	}

};

class CarIterator
{
	const CarCollection &car;
	int index;
public:
	CarIterator(const CarCollection &s) : car(s)
	{
		index = 0;
	}
	void operator++()
	{
		index++;
	}
	void operator--()
	{
		index--;
	}
	bool operator()()
	{
		return index != 5;
	}
	Car operator *()
	{
		return car.items[index];
	}
};
