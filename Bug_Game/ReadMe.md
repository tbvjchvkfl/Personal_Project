
Bug's Game
-
해당 게임은 DirectX2D로 만들었습니다.
총 2개의 스테이지로 구성되어있으며, 1스테이지에서는 화면에 보이는 벌레와 부딪혀 잡아먹으면 클리어, 2스테이지에서는 플레이어를 향해 날아오는 벌레들을 마우스로 클릭하여 없애주면 되는 게임입니다.

플레이 영상
-
https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/ea1e1ef8-9990-4ad3-a1ae-f819a8768bef

제작 기간 & 사용 기술
-
> #### 제작 기간
>   - 30일 소요 ( 개인 )

> #### 사용 기술
>   - C++ & DirectX 2D

클래스 구조
-
![Class Diagram](https://github.com/tbvjchvkfl/Personal_Project/assets/137769043/a3b02ea4-32fd-4111-844b-d6827675363a)


핵심 기술
-
> ### COM
>   - 초기 프레임워크를 만들 때 COM 오브젝트에 대해 공부했었고, 프레임워크를 COM을 이용하여 만들었습니다.
<pre>
  <code>
    HRESULT D2DFramework::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
    {
    	ThrowIfFailed(CoInitialize(nullptr));
    
    	ThrowIfFailed(InitWindow(hInstance, title, w, h));
    	ThrowIfFailed(InitD2D(mHwnd), "Failed To InitD2D");
    
    
    	HRESULT hr = BitmapManager::Instance().Initialize(mspRenderTarget.Get());
    	ThrowIfFailed(hr, "Failed To BitmapManager Initialize");
    
    	ShowWindow(mHwnd, SW_SHOW);
    	UpdateWindow(mHwnd);
    
    	return S_OK;
    }
    
    void D2DFramework::Release()
    {
    	BitmapManager::Instance().Release();
    	mspRenderTarget.Reset();
    	mspD2DFactory.Reset();
    
    	CoUninitialize();
    }
  </code>
</pre>

> ### Microsoft::WRL::Comptr
>   - D2D 인터페이스를 사용할 때 C++ 스마트포인터를 사용하려 했으나, C++ 스마트 포인터와 COM오브젝트의 다른 수명주기로 인해 Microsoft::WRL::ComPtr를 사용하였습니다.
<pre>
  <code>
      Microsoft::WRL::ComPtr<ID2D1Factory> mspD2DFactory{};
      Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mspRenderTarget{};
      Microsoft::WRL::ComPtr<IDWriteFactory> mspWriteFactory{};
      Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> mspTextBrush{};
  </code>  
</pre>

> ### Bitmap
>  - 화면에 그릴 요소들을 Bitmap으로 불러오기 위해 IWICImagingFactory와 ID2D1Bitmap 인터페이스를 사용하여 이미지파일의 픽셀 데이터를 비트맵으로 변환하였습니다.
<pre>
  <code>
    HRESULT BitmapManager::LoadWICBitmap(wstring filename, ID2D1Bitmap** ppBitmap)
    {
    	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
    	HRESULT hr;
    
    	auto pWICFactory = mspWICFactory.Get();
    
    	if (pWICFactory == nullptr)
    	{
    		return E_FAIL;
    	}
        
      // 디코더 생성
    	hr = pWICFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf());
    
    	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode>frame;
    	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;

      // 포멧 컨버터 초기화
    	hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
    	
      auto pRT = mpRenderTarget;
    	if (pRT == nullptr)
    	{
    		return E_FAIL;
    	}

      // 비트맵 그리기
    	hr = pRT->CreateBitmapFromWicBitmap(converter.Get(), ppBitmap);
    	return S_OK;
    }
    
  </code>
</pre>

시행착오
-
> - Bug와 Player가 충돌했을 때 발생하는 상호작용을 구현하기 위해 Bug 클래스에서 Player의 포인터를 선언하여 Bug와 Player 간의 충돌 상호작용 기능을 구현하려 했었습니다. 충돌이라는 인터렉션은 Bug클래스에서 관련 함수를 가지고 있는게 좋겠다고 생각하여 Bug클래스에 Player를 가리키는 포인터를 선언하고 작업을 진행하였으나, Player의 객체를 가져올 방법을 찾지 못해 BugsGame(GameLoop용 클래스)클래스에서 Player클래스를 스마트 포인터로 받아와 Bug클래스에 있는 Collision메소드를 호출하였으나, 실제 플레이어와 인터렉션하던 Player개체와 Bug의 상호작용이 발생하지 않는 현상이 발생했습니다. 이후 구글링과 기존에 공부했던 C++ SmartPointer자료와 Pointer에 대한 자료들을 다시 보며 코드를 바라보았을 때, BugsGame(Gameloop용 클래스)클래스에서 사용했던 Player스마트포인터에 대한 참조가 기존 이미 생성된 개체가 아닌 새로운 개체를 생성하여 상호작용하게끔 동작하고 있었다는 것을 알게 되었고, Bug의 생성자의 인자로 Player를 받아와 Bug클래스에서 Collision함수를 구현해주었고, shared_ptr를 사용하여 문제를 해결했습니다.

> - Bug의 위치는 화면 범위내에 랜덤한 위치 값을 구해 배치되게 구현했었는데, 1단계를 클리어하고 2단계로 넘어가면서 중앙에 고정되는 Player의 바로 옆에 Bug가 생성되면서 게임이 너무 빨리 끝나버리는 현상이 있었습니다. 해당 내용을 수정하기 위해 벌레가 생성되는 위치를 1단계와 2단계에서 서로 다르게 해주어야했었는데, 처음엔 2단계로 진입하면서 벌레를 생성할 때 벌레들을 넣었던 List를 4개로 늘려 상하좌우에서 각각 실행되게 하려했으나, 미련하다는 생각이 들어 화면 전체 범위를 구한 후 임의의 사각형을 화면 중앙으로부터 하나 더 그려 해당 범위가 아닌 범위에서 벌레들이 생성되게 구현하였습니다.

> - Player와 Bug가 화면 안에서 상호작용하는 것을 의도하고 기능을 구현했었으나, 이동하면서 화면 밖으로 나가버리는 현상이 발생했습니다. 이에 화면의 크기를 구해 Player와 Bug의 Bitmap이 각 화면에 닿으면 더이상 좌표 이동을 할 수없도록 구현하여 해결했습니다.
