## KeFuckingNoob

### Derleme Gereksinimleri
 - Visual Studio 2017 ve üstü 
 - Windows 10 SDK
 - WDK

#### Driver Başlatma

      # Test modunu aktif edin ve bilgisayarınız yeniden başlatın
	  bcdedit /set testsigning on

	  # Servisi oluşturun ve başlatın
	  sc create simhi type= kernel binpath="C:\Users...\Desktop\KeFuckingNoobD.sys"
	  sc start simhi
	 
	  # İşiniz bittiğinde servisi sonlandırın
	  sc stop simhi
  
	  # Geliştirme bittiğin test modunu kapatın
	  bcdedit /set testsigning off



**Nasıl Kullanılacağı Sizin Hayal Gücünüze Bağlı :blush:**