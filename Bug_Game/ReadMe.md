
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

