#pragma once

#include "Zinet/GraphicLayer/ZtTexture.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtTextureTests : public ::testing::Test
{
protected:

	ZtTextureTests()
	{
		Window.InitGLFW();
		Window.CreateWindow();
		Window.InitGLAD();
		Window.InitOpenGL();
	}

	~ZtTextureTests()
	{
		Texture.Delete();
	}

	ZtTexture Texture;
	ZtWindow Window;

};

TEST_F(ZtTextureTests, GenerateTest)
{
	Texture.Generate();
	GLuint ActualID = Texture.GetID();
	GLuint NotExpectedID = ZtTexture::InvalidID;

	ASSERT_NE(ActualID, NotExpectedID);
}

TEST_F(ZtTextureTests, GetIDTest)
{
	GLuint ID = Texture.GetID();
}

TEST_F(ZtTextureTests, BindTest)
{
	Texture.Generate();
	Texture.Bind();
	GLint ActualBindedTexture2D = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &ActualBindedTexture2D);
	GLuint ExpectedBindedTexture2D = Texture.GetID();

	ASSERT_EQ(ActualBindedTexture2D, ExpectedBindedTexture2D);
}

TEST_F(ZtTextureTests, UnbindTest)
{
	Texture.Generate();
	Texture.Bind();
	Texture.Unbind();

	GLint ActualBindedTexture2D = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &ActualBindedTexture2D);
	GLuint NotExpectedBindedTexture2D = Texture.GetID();

	ASSERT_NE(ActualBindedTexture2D, NotExpectedBindedTexture2D);
}

TEST_F(ZtTextureTests, DeleteTest)
{
	Texture.Generate();
	Texture.Bind();
	GLuint PreviousID = Texture.GetID();
	Texture.Delete();

	GLboolean IsTexture = glIsTexture(PreviousID);
	ASSERT_FALSE(IsTexture);

	GLuint ActualID = Texture.GetID();
	GLuint ExpectedID = ZtTexture::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtTextureTests, LoadFromDataTest)
{
	Texture.Generate();
	Texture.Bind();

	unsigned char* Data = nullptr;
	GLsizei Width{};
	GLsizei Height{};
	Texture.LoadFromData(Data, Width, Height);
}

TEST_F(ZtTextureTests, LoadFromFileTest)
{
	Texture.Generate();
	Texture.Bind();

	ZtFileFinder FileFinder;
	ZtFileFinder::Path RootPath = FileFinder.CurrentProjectRootPath();
	ZtFileFinder::Path FilePath = RootPath / "Textures" / "wall.jpg";
	Texture.LoadFromFile(FilePath);
}

TEST_F(ZtTextureTests, GenerateMipmapTest)
{
	Texture.GenerateMipmap();
}