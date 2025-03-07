/*++

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

 */

import * as asmCrypto from "asmcrypto-lite";

import * as Assert from "./AMCAsserts.js";
import * as Common from "./AMCCommon.js"


export default class AMCUpload extends Common.AMCObject {
	
	constructor (itemState, streamuuid, contextuuid) 
	{		
		super ();
		
		Assert.ObjectInstance (itemState, "amcUploadState");
		Assert.UUIDValue (streamuuid);
		Assert.UUIDValue (contextuuid);
		
		this.registerClass ("amcUpload");
								
		this.itemState = itemState;
		this.uploadID = Assert.IntegerValue (itemState.getUploadID ());
		this.streamuuid = streamuuid;
		this.contextuuid = contextuuid;
		this.sha256sum = Common.nullToken ();
		this.successEvent = "";
		this.failureEvent = "";
		
		this.fileToUpload = itemState.getChosenFile ();
		this.fileName = Assert.StringValue (this.fileToUpload.name);
		
		// Get upload size and chunk count
		this.fileSize = Assert.IntegerValue (this.fileToUpload.size);
		this.chunkSize = 128 * 1024;		
		if (this.fileSize <= 0)
			throw "invalid upload size";		
		this.chunkCount = Math.floor ((this.fileSize + this.chunkSize - 1) / this.chunkSize);
		this.currentPosition = 0;

		// Create SHA Instance
		this.shaInstance = new asmCrypto.SHA256();
		this.shaInstance.reset();
				
	}
		

	bytesToHex (buffer) {
		let hex = "";
		let n;
		for (n in buffer) {
			hex += ("0" + (0xff & buffer[n]).toString(16)).slice(-2);
		}
		return hex;
	}
	
	
	getFileName ()
	{
		return this.fileName;
	}
			
	getFileSize ()
	{
		return this.fileSize;
	}

	getCurrentPosition ()
	{
		return this.currentPosition;
	}

	getProgressString ()
	{
		let percent = 0.0;
		if (this.fileSize > 0) {			
			percent = (this.currentPosition * 100.0 / this.fileSize);			
		}
		
		let fullPercent = Math.floor (percent);
		let tenthPercent = Math.floor ((percent - fullPercent) * 10.0);
		
		return fullPercent.toString () + "." + tenthPercent.toString () + "%";		
	}
	
	readChunk (ownerInstance, callback) 
	{
		Assert.ObjectInstance (ownerInstance, "amcObject");
		
		if (this.currentPosition > this.fileSize)
			throw "invalid chunk read position";
		
		let bytesToRead = this.chunkSize;
		if ((this.currentPosition + bytesToRead) > this.fileSize) {
			bytesToRead = this.fileSize - this.currentPosition;
		}
		
		if (bytesToRead > 0) {
			let chunk = this.fileToUpload.slice (this.currentPosition, this.currentPosition + bytesToRead);
			
			let reader = new FileReader();

			reader.onload = () => {
				let dataBuffer = reader.result;
				
				if (bytesToRead == dataBuffer.byteLength) {
					
					let uploadOffset = this.currentPosition;
				
					this.currentPosition = this.currentPosition + bytesToRead;
					
					this.shaInstance.process (dataBuffer);
					if (callback)
						callback (ownerInstance, this, dataBuffer, uploadOffset);
				}
				
			}
			
			reader.readAsArrayBuffer(chunk);
			
			return true;
		}
		
		
		return false;
	}
	
	
	setStateMessageToProgress ()
	{
		if (this.itemState) {
			Assert.ObjectValue (this.itemState);
			
			this.itemState.setMessage (this.itemState.progressMessage + " (" + this.getProgressString () + ")");
		}
	}
	
	setStateMessageToWaiting ()
	{
		if (this.itemState) {
			Assert.ObjectValue (this.itemState);
			
			this.itemState.setMessage (this.itemState.waitMessage);
		}
	}
	
	setStateMessageToPreparing ()
	{
		if (this.itemState) {
			Assert.ObjectValue (this.itemState);
			
			this.itemState.setMessage (this.itemState.buildMessage);
		}
	}
	
	calculateChecksum ()
	{
		this.shaInstance.finish();
		this.sha256sum = this.bytesToHex (this.shaInstance.result);
		this.shaInstance.reset();
		
		return this.sha256sum;		
	}
	
	getChecksum ()
	{
		return this.sha256sum;		
	}
	
	checkIfUploadIsActive ()
	{
		if (this.itemState) {
			return (this.itemState.getUploadID () === this.uploadID);
		} else {
			return false;
		}
	}
	
	clearUploadState ()
	{
		if (this.itemState) {
			this.itemState.finishUpload ();
		}
	}
	
	hasSuccessEvent ()
	{
		if (this.successEvent) 
		{
			return true;
		}
		
		return false;		
	}
	
	setSuccessEvent (eventName) 
	{
		this.successEvent = Assert.StringValue (eventName);
	}
	
	getSuccessEvent ()
	{
		return this.successEvent;
	}

	hasFailureEvent ()
	{
		if (this.failureEvent) 
		{
			return true;
		}
		
		return false;		
	}
	
	getFailureEvent ()
	{
		return this.failureEvent;
	}
	
	setFailureEvent (eventName) 
	{
		this.failureEvent = Assert.StringValue (eventName);
	}
	
	getItemUUID ()
	{
		Assert.ObjectInstance (this.itemState, "amcUploadState");
		return this.itemState.getItemUUID ();
	}


}

