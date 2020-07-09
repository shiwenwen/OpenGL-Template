//
//  main.m
//  OpenGLDemo
//
//  Created by 首佑-石文文 on 2020/7/9.
//  Copyright © 2020 首佑-石文文. All rights reserved.
//

#include "GLShaderManager.h"

#include "GLTools.h"

#include <glut/glut.h>

GLBatch triangleBatch; // 辅助批次类，可以传输顶点/光照/纹理/颜色数据到存储着色器中

GLShaderManager shaderManager; //存储着色器管理




/// 窗口大小改变时回调
/// @param w 窗口宽度
/// @param h 窗口高度
void ChangeSize(int w,int h) {
    // 设置视口位置和大小，其中0,0代表窗口中视口的左下角坐标，w，h代表宽高像素，此处设置与窗口一样大小。
    glViewport(0,0, w, h);
    
}

//为程序作一次性的设置
void SetupRC() {
    
    //设置背影颜色
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    
    //初始化着色管理器
    shaderManager.InitializeStockShaders();
    
    //设置三角形，其中数组vVert包含所有3个顶点的x,y,笛卡尔坐标对。
    GLfloat vVerts[] = {
        -0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f,
    };
    
    //批次处理
    triangleBatch.Begin(GL_TRIANGLES,3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
}

//开始渲染
void RenderScene(void) {
    
    //清除一个或一组特定的缓冲区，如果不清楚需要清除的缓冲区，可以全部都清除
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    
    //设置一组浮点数来表示红色
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    
    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    
    //提交着色器
    triangleBatch.Draw();
    
    //将在后台缓冲区进行渲染，然后在结束时交换到前台
    glutSwapBuffers();
    
}

int main(int argc,char* argv[]) {
    
    //设置当前工作目录，针对MAC OS X
    gltSetWorkingDirectory(argv[0]);
    
    //初始化GLUT库
    glutInit(&argc, argv);
    
    
    /*
     初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区
     */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //GLUT窗口大小，标题窗口
    glutInitWindowSize(800,600);
    // 窗口名称
    glutCreateWindow("Triangle");
    
    //注册回调函数 reshape在初次出现和每次改变窗口大小时触发回调
    glutReshapeFunc(ChangeSize);
    
    //显示回调函数，注册一个用于场景绘制的函数
    glutDisplayFunc(RenderScene);
    
    //驱动程序的初始化
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        fprintf(stderr,"glew error:%s\n",glewGetErrorString(err));
        return 1;
    }
    
    //调用SetupRC 初始化着色器配置
    SetupRC();
    
    glutMainLoop(); // 启动OpenGL运行循环
    return 0;
    
}

