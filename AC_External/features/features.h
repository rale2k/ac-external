#pragma once

class Features {
public:
	bool aimbot{ false };
	bool autoshoot{ false };
	bool esp{ false };
	bool no_recoil{ false };
	bool silencer{ false };

	Features();

	void initialize();

	void AimBot();
	void ESP(Paint* paint);
	void NoRecoil();
	void Silencer();
};

extern Features* features;