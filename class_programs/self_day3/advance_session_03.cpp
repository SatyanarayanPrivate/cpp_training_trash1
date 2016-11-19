#include <iostream>
#include <map>
using namespace std;

namespace DecoratorPattern {
	//decorator pattern:: dynamic extension of behaviour
	class ITunnel {
	public:
		virtual void TunnelMessage(char * msg) = 0x00;
	};

	//NULL Object pattern
	class NullTunnel :public ITunnel {
	public:
		void TunnelMessage(char *msg) {
		}
	};

	class TunnelHelper :public ITunnel {
		ITunnel *tunnel;
	protected:
		TunnelHelper(ITunnel *tnl) :tunnel(tnl) {
		}
	public:
		void TunnelMessage(char *msg) {
			tunnel->TunnelMessage(msg);
		}
	};

	class LogTunnel :public TunnelHelper {
	public:
		LogTunnel(ITunnel *tnl) : TunnelHelper(tnl) {

		}
		void TunnelMessage(char *msg) {
			cout << "Logging msg (" << msg << ")" << endl;
			TunnelHelper::TunnelMessage(msg);
		}
	};

	class EncodeTunnel :public TunnelHelper {
	public:
		EncodeTunnel(ITunnel *tnl) : TunnelHelper(tnl) {

		}
		void TunnelMessage(char *msg) {
			cout << "Encoding msg (" << msg << ")" << endl;
			TunnelHelper::TunnelMessage(msg);
		}
	};

	class EncrytorTunnel :public TunnelHelper {
	public:
		EncrytorTunnel(ITunnel *tnl) : TunnelHelper(tnl) {

		}
		void TunnelMessage(char *msg) {
			cout << "Encryting msg (" << msg << ")" << endl;
			TunnelHelper::TunnelMessage(msg);
		}
	};

	class TunnelFactory {
		TunnelFactory() {
		}
		~TunnelFactory() {
		}
	public:
		static ITunnel *CreateTunnels() {
			//return NULL;
			//return new NullTunnel();	// should use null object
			return new EncrytorTunnel(new EncodeTunnel(new LogTunnel(new NullTunnel())));
		}
	};

	void main() {
		cout << "Business Started ..." << endl;
		ITunnel *tun1 = TunnelFactory::CreateTunnels();
		tun1->TunnelMessage("India is great !!!");
		//Log
		cout << "Business Completed ..." << endl;
	}
}

// Abstract Factory:: switching between family of components
class IVideo {
public:
	virtual void CreateVideo() = 0;
	virtual void PlayVideo() = 0;
};

class IAudio {
public:
	virtual void CreateAudio() = 0;
	virtual void PlayAudio() = 0;
};

class IMagnifier {
public:
	virtual void CreateMagnifier() = 0;
	virtual void AttachMagnifier() = 0;
};

class IEVideo:public IVideo {
public:
	virtual void CreateVideo() {
		cout << "IE Video Created" << endl;
	}
	virtual void PlayVideo() {
		cout << "IE Video Playing" << endl;
	}
};

class IEAudio: public IAudio {
public:
	virtual void CreateAudio() {
		cout << "IE Audio Created" << endl;
	}
	virtual void PlayAudio() {
		cout << "IE Audio Playing" << endl;
	}
};

class IEMagnifier:public IMagnifier {
public:
	virtual void CreateMagnifier() {
		cout << "IE Magnifier Created" << endl;
	}
	virtual void AttachMagnifier() {
		cout << "IE Magnifier Attached" << endl;
	}
};

class ChromeVideo:public IVideo {
public:
	virtual void CreateVideo() {
		cout << "Chrome Video Created" << endl;
	}
	virtual void PlayVideo() {
		cout << "Chrome Video Playing" << endl;
	}
};

class ChromeAudio: public IAudio {
public:
	virtual void CreateAudio() {
		cout << "Chrome Audio Created" << endl;
	}
	virtual void PlayAudio() {
		cout << "Chrome Audio Playing" << endl;
	}
};

class ChromeMagnifier: public IMagnifier {
public:
	virtual void CreateMagnifier() {
		cout << "Chrome Magnifier Created" << endl;
	}
	virtual void AttachMagnifier() {
		cout << "Chrome Magnifier Attached" << endl;
	}
};

class IFactory {
public:
	virtual IVideo *CreateVideo() = 0;
	virtual IAudio *CreateAudio() = 0;
	virtual IMagnifier *CreateMagnifier() = 0;
};

class IEFactory : public IFactory {
public:
	virtual IVideo *CreateVideo() {
		return new IEVideo();
	}
	virtual IAudio *CreateAudio() {
		return new IEAudio();
	}
	virtual IMagnifier *CreateMagnifier() {
		return new IEMagnifier();
	}
};

class ChromeFactory : public IFactory {
public:
	virtual IVideo *CreateVideo() {
		return new ChromeVideo();
	}
	virtual IAudio *CreateAudio() {
		return new ChromeAudio();
	}
	virtual IMagnifier *CreateMagnifier() {
		return new ChromeMagnifier();
	}
};
/*
IFactory *ReturnIEFactory() {
	return new IEFactory();
}
IFactory *ReturnChromeFactory() {
	return new ChromeFactory();
}

typedef IFactor *(*FPTR)();
class Dummy {
	static map<string, FPTR fp> Mymap;
public:
	/*Dummy() {
		Mymap["Ie"] = ReturnIEFactory;
		Mymap["Chrome"] = ReturnChromeFactory;
	}
};*/

void main() {
	IFactory *fact = new IEFactory();
	IVideo *video = fact->CreateVideo();//new IEVideo();
	video->CreateVideo();
	video->PlayVideo();
	IAudio *aud = fact->CreateAudio();//new IEAudio();
	aud->CreateAudio();
	aud->PlayAudio();
	IMagnifier *mag = fact->CreateMagnifier();//new IEMagnifier();
	mag->CreateMagnifier();
	mag->AttachMagnifier();
}