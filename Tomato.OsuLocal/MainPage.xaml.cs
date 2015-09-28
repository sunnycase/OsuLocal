using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Tomato.Osu.Core;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Tomato.OsuLocal
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Catel.Windows.Controls.Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            LoadState();
            base.OnNavigatedTo(e);
        }

        private Uri filePath = new Uri(@"ms-appx:///Assets/313982 AiM - Ashita wa Atashi no Kaze ga Fuku (TV Size)/AiM - Ashita wa Atashi no Kaze ga Fuku (TV Size) (Kencho) [Easy].osu");

        private async void LoadState()
        {
            var reader = new BeatmapReader();
            var source = await Windows.Storage.FileIO.ReadTextAsync(await StorageFile.GetFileFromApplicationUriAsync(filePath));
            var map = reader.Read(source);

            map.ToString();
        }
    }
}
