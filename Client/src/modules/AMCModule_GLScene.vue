<!--

Copyright (C) 2020 Autodesk Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the Autodesk Inc. nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AUTODESK INC. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

!-->

<template>
	
	<div v-if="(module.type == 'glscene')" style="width:100%; height:100%; display:block; overflow:hidden;">
		
			<div ref="glDiv" style="width:100%;height:100%;"  v-resize="onResize" />
		
	</div>

</template>

<script>

	import WebGLImpl from "../common/AMCImplementation_WebGL.js"

	export default {
		props: ["Application", "module"],
	  
		components: {
		},
		
		data: () => ({				
			glInstance: null
		}),
		
		methods: {
			    animate: function () {
					requestAnimationFrame(this.animate);
					
					if (this.mesh) {
						const time = Date.now() * 0.001;

						this.mesh.rotation.y = time * 0.4;
					}

					if (this.glInstance)
						this.glInstance.renderScene ();

				},
				
				onResize: function () {
					var domelement = this.$refs.glDiv; 
					if (!domelement) 
						return;	
						
					if (!this.LayerViewerInstance) 
						return;
						
					this.LayerViewerInstance.updateSize (domelement.clientWidth, domelement.clientHeight);
				},
		},
		
		
		created () {
			this.glInstance = this.Application.retrieveWebGLInstance (module.uuid);
			if (!this.glInstance) {
				this.glInstance = new WebGLImpl ();
				this.Application.storeWebGLInstance (this.glInstance);
								
			}
		},
		
		mounted() {
				
			const glDiv = this.$refs.glDiv;
			if (glDiv && this.glInstance) {						
			
				var width = glDiv.clientWidth;
				var height = glDiv.clientHeight;
				if ((width > 0) && (height > 0)) {
					this.glInstance.setup2DView (width, height, 0.1, 100);					
					this.glInstance.resizeTo (width, height);
					this.glInstance.setupDOMElement (glDiv);														
					this.mesh = this.glInstance.setupDemoScene ();
					this.animate();
				}
				
			}
		}
		
	};
	
</script>