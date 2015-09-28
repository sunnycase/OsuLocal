//
// Tomato Osu Local
// Beatmap 模型
// 作者：SunnyCase
// 创建时间：2015-09-28
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Catel.Data;

namespace Tomato.OsuLocal.Models
{
    /// <summary>
    /// Beatmap 模型
    /// </summary>
    class BeatmapModel : ModelBase
    {
        /// <summary>
        /// 视频 Uri
        /// </summary>
        public Uri VideoUri { get; set; }

        /// <summary>
        /// 图片 Uri
        /// </summary>
        public Uri ImageUri { get; set; }
    }
}
