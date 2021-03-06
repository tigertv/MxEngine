// Copyright(c) 2019 - 2020, #Momo
// All rights reserved.
// 
// Redistributionand use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
// 
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditionsand the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditionsand the following disclaimer in the documentation
// and /or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "GLIndexBuffer.h"
#include "Platform/OpenGL/GLUtilities/GLUtilities.h"
#include "Core/Macro/Macro.h"

namespace MxEngine
{
	GLIndexBuffer::GLIndexBuffer()
	{
		this->id = 0;
	}

	GLIndexBuffer::GLIndexBuffer(IndexData data, size_t count)
	{
		Load(data, count);
	}

	GLIndexBuffer::GLIndexBuffer(GLIndexBuffer&& ibo) noexcept
		: count(ibo.count)
	{
		this->id = ibo.id;
		ibo.id = 0;
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		if (this->id != 0)
		{
			GLCALL(glDeleteBuffers(1, &id));
		}
	}

	void GLIndexBuffer::Load(IndexData data, size_t count)
	{
		this->count = count;
		if (id == 0)
		{
			GLCALL(glGenBuffers(1, &id));
		}
		this->Bind();
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(IndexType), data, GL_STATIC_DRAW));
	}

	void GLIndexBuffer::Unbind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	size_t GLIndexBuffer::GetCount() const
	{
		return count;
	}

	size_t GLIndexBuffer::GetIndexTypeId() const
	{
		return GL_UNSIGNED_INT;
	}

	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
}