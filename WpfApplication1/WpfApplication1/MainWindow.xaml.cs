
using SharpGL.Shaders;
using SharpGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using System.Runtime.InteropServices;



namespace WpfApplication1
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        uint shader1, shader2, vertexBufferPos, colorBufferPos;

        private void OpenGLControl_OpenGLDraw(object sender, SharpGL.SceneGraph.OpenGLEventArgs args)
        {
            //  Get the OpenGL instance that's been passed to us.
            OpenGL gl = args.OpenGL;

            //  Clear the color and depth buffers.
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);

            gl.BindBuffer(OpenGL.GL_ARRAY_BUFFER, vertexBufferPos);
            gl.BindBuffer(OpenGL.GL_ARRAY_BUFFER, colorBufferPos);

            gl.DrawArrays(OpenGL.GL_COLOR, 0, 3);
            
            




            //  Flush OpenGL.
            gl.Flush();


        }



        private void OpenGLControl_OpenGLInitialized(object sender, SharpGL.SceneGraph.OpenGLEventArgs args)
        {

            OpenGL gl = args.OpenGL;

            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));
            //create shader

            Console.WriteLine(gl.Version);
            shader1 = gl.CreateShader(OpenGL.GL_VERTEX_SHADER);
            shader2 = gl.CreateShader(OpenGL.GL_FRAGMENT_SHADER);
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()) + " " + shader1.ToString());
            gl.ShaderSource(shader1, "minimal.vert");
            gl.CompileShader(shader1);
            gl.ShaderSource(shader2, "minimal.frag");
            gl.CompileShader(shader2);
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()) + " " + shader2.ToString());
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));
            uint program = gl.CreateProgram();
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));

            gl.BindAttribLocation(program, 0, "in_Position");
            gl.BindAttribLocation(program, 1, "in_Color");

            gl.AttachShader(program, shader1);
            gl.AttachShader(program, shader2);
            Console.WriteLine(gl.IsProgram(program));
            gl.LinkProgram(program);
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));
            //gl.UseProgram(program);

            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));

            //criaçao dos vbo's
            float[] vertexPositions = {
                                      -1.0f, -1.0f, -5.0f,
                                       1.0f, -1.0f, -5.0f,
                                       0.0f,  1.0f, -5.0f,
                                      };


            uint[] vbo = new uint[1];
            gl.GenBuffers(1, vbo);

            vertexBufferPos = vbo[0];

            gl.BindBuffer(OpenGL.GL_ARRAY_BUFFER, vertexBufferPos);

            gl.BufferData(OpenGL.GL_ARRAY_BUFFER, vertexPositions, OpenGL.GL_STATIC_DRAW);

            gl.VertexAttribPointer(0, 3, OpenGL.GL_FLOAT, false, 0, IntPtr.Zero);

            gl.EnableVertexAttribArray(0);

            //criação das cores
            float[] colors = {1.0f, 0.0f, 0.0f,
                              1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f,
                             };

            uint[] cbo = new uint[1];
            gl.GenBuffers(1, cbo);
            colorBufferPos = cbo[0];
            gl.BindBuffer(OpenGL.GL_ARRAY_BUFFER, colorBufferPos);
            gl.BufferData(OpenGL.GL_ARRAY_BUFFER, colors, OpenGL.GL_STATIC_DRAW);
            gl.VertexAttribPointer(1, 3, OpenGL.GL_FLOAT, false, 0, IntPtr.Zero);
            gl.EnableVertexAttribArray(1);
            Console.WriteLine(gl.GetErrorDescription(gl.GetError()));
        }

        private void OpenGLControl_Resized(object sender, SharpGL.SceneGraph.OpenGLEventArgs args)
        {
            // Get the OpenGL instance.
            OpenGL gl = args.OpenGL;

            // Load and clear the projection matrix.
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();

            // Perform a perspective transformation
            gl.Perspective(45.0f, (float)gl.RenderContextProvider.Width /
                (float)gl.RenderContextProvider.Height,
                0.1f, 100.0f);

            // Load the modelview.
            gl.MatrixMode(OpenGL.GL_MODELVIEW);
        }
    }


}
