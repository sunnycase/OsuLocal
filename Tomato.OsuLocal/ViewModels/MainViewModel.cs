//
// Tomato Osu Local
// 主视图模型
// 作者：SunnyCase
// 创建时间：2015-09-28
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Catel.MVVM;
using Tomato.OsuLocal.Models;

namespace Tomato.OsuLocal.ViewModels
{
    /// <summary>
    /// 主视图模型
    /// </summary>
    class MainViewModel : ViewModelBase
    {
        /// <summary>
        /// 当前 Beatmap
        /// </summary>
        public BeatmapModel CurrentBeatmap { get; private set; }

        public MainViewModel()
        {
            CurrentBeatmap = new BeatmapModel
            {
                ImageUri = new Uri("ms-appx:///Assets/313982 AiM - Ashita wa Atashi no Kaze ga Fuku (TV Size)/BG.jpg"),
                VideoUri = new Uri("ms-appx:///Assets/313982 AiM - Ashita wa Atashi no Kaze ga Fuku (TV Size)/video.avi"),
            };
        }
    }
}
