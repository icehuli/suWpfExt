using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


using System.Windows.Threading;
using System.Collections;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Windows.Interop;

using suExtMainWrapper;


namespace suWpfUI
{
    /// <summary>
    /// Interaction logic for UserControl1.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow(MyExtMainWrapper extMainWrapper, MainWindowWrapper mainWindowWrapper, Dispatcher theSodAccessDispatcher)
        {
            this.Closing += MainWindow_Closing;
            InitializeComponent();
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.Visibility = Visibility.Hidden;
        } 

        public void SetDictionaries(XmlDocument xml)
        {
            XmlDataProvider selection = FindResource("selection") as XmlDataProvider;
            selection.Document = xml;
        }

        private void Rectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }
    }
}
