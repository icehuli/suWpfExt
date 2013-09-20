
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;
using System.Windows.Threading;
using System.Threading;
using System.Globalization;
using System.Windows;

using suExtMainWrapper;
using System.Windows.Data;

namespace suWpfUI
{
    public class MainWindowWrapper
    {
        
        private MainWindow mainWpf = null;
        private MyExtMainWrapper extMainWrapper = null;

        public MainWindowWrapper(MyExtMainWrapper aMyExtMainWrapper, int ID)
        {
            extMainWrapper = aMyExtMainWrapper;

            if (ID == 1 || true)
            {
                Dispatcher sodAccessDispatcher = Dispatcher.CurrentDispatcher;

                Thread thread = new Thread(() =>
                {
                    MainWindow w = new MainWindow(extMainWrapper, this, sodAccessDispatcher);
                    mainWpf = w;

                    Boolean modal = false;
                    if (modal)
                    {
                        // ShowDialog automatically starts the event queue for the new windows in the new thread. 
                        // The window isn't modal though.
                        w.ShowDialog();
                    }
                    else
                    {
                        w.Show();

                        w.Closed += (sender2, e2) =>
                        {
                            w.Dispatcher.InvokeShutdown();
                        };

                        System.Windows.Threading.Dispatcher.Run();
                    }
                });

                thread.SetApartmentState(ApartmentState.STA);
                thread.CurrentCulture = CultureInfo.CreateSpecificCulture("en-US");
                thread.Start();
                Console.WriteLine("after Start");
            }
            else
            {

            }
        }

        public void ShowMainWindow()
        {
            mainWpf.Dispatcher.BeginInvoke((Action) (() =>
            {
              mainWpf.Show();
              mainWpf.Activate();
            }), System.Windows.Threading.DispatcherPriority.ContextIdle, null);
        }

        public void HideMainWindow()
        {
            mainWpf.Dispatcher.BeginInvoke((Action)(() =>
            {
                mainWpf.Hide();
            }), System.Windows.Threading.DispatcherPriority.ContextIdle, null);
        }

        public void ToggleMainWindow()
        {
          mainWpf.Dispatcher.BeginInvoke((Action)(() =>
          {
            if (mainWpf.Visibility == Visibility.Hidden)
            {
              mainWpf.Visibility = Visibility.Visible;
              if (mainWpf.WindowState == WindowState.Minimized)
              {
                mainWpf.WindowState = WindowState.Normal;
              }
            }
            else if (mainWpf.Visibility == Visibility.Visible && mainWpf.WindowState != WindowState.Minimized)
            {
              mainWpf.Visibility = Visibility.Hidden;
            }
            else if (mainWpf.Visibility == Visibility.Visible && mainWpf.WindowState == WindowState.Minimized)
            {
              mainWpf.WindowState = WindowState.Normal;
            }
            else if (mainWpf.Visibility == Visibility.Collapsed)
            {
              mainWpf.Visibility = Visibility.Visible;
              if (mainWpf.WindowState == WindowState.Minimized)
              {
                mainWpf.WindowState = WindowState.Normal;
              }
            }
            //mainWpf.Hide();
          }), System.Windows.Threading.DispatcherPriority.ContextIdle, null);
        }

        public void SetDictionaries(XmlDocument xml)
        {
            mainWpf.Dispatcher.BeginInvoke((Action)(() =>
            {
                mainWpf.SetDictionaries(xml);
            }), System.Windows.Threading.DispatcherPriority.ContextIdle, null);
        }

    }
}
