using System;
using Catel.IoC;

namespace Tomato.OsuLocal
{
    static class ModuleInitializer
    {
        public static void Initialize()
        {
            RegisterServices();
        }

        private static void RegisterServices()
        {
            //IoCConfiguration.DefaultServiceLocator.RegisterType<IThemeService, ThemeService>();
        }
    }
}