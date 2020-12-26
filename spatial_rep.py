class objCentered():
    def __init__(self):
        self.references = {}

    def parse(self, refName, objSide=None):
        if refName in self.references and not objSide:
            # remove
            self.references.pop(refName)
        # error
        elif refName in self.references and objSide:
            return 'Cannot add an reference object nowhere in relation to the center'
        else:
            # add or modify
            self.references[refName] = objSide

    def getViewerRelPosition(self, refName):
        ''' Returns the position of the viewer as if they were the reference obj
        '''
        if refName in self.references:
            return 'The ' + refName + ' is to the ' + self.references[refName] +\
                   ' of the center Object and the center Object is to the front of\
                    the viewer, by default for this class'
        else:
            return 'Error, bad refName'


class viewerCentered():
    def __init__(self, front, left, back, right, name):
        self.viewers = {}
        self.centerReferences = [front, left, back, right, name]
        self.validPOVs = ['front', 'left', 'back', 'right']

    def parse(self, viewer, subj, ref, pov=None):
        ''' the subject is to the pov of the ref. cannot place viewer in a singular
        half-plane without the use of the center object
        '''
        if viewer in self.viewers and not pov:
            # remove
            self.viewers.pop(viewer)
        # error
        elif viewer in self.viewers and pov:
            return 'Cannot add an viewer nowhere in relation to the center'
        elif subj == ref:
            return 'Cannot refernce an object onto itself'
        else:
            if subj in self.centerReferences and ref in self.centerReferences and pov in self.validPOVs:
                if subj == self.centerReferences[-1] or ref == self.centerReferences[-1]:
                    self.viewers[viewer] = [subj, ref, pov]
                # error
                else:
                    return 'Cannot determine viewer position without center to give relation context'
            # error
            else:
                return 'Cannot determine viewer position without using valid reference objects and pov'

    def getCenterRelPosition(self, subj, ref, pov):
        ''' to transfer from viewer to center oriented. returns viewer's position
        relative to the center obj
        '''
        index = self.centerReferences.index(subj)
        # base case: obj is to pov of the center
        if ref == self.centerReferences[-1]:
            # front is dont care
            if pov == 'back':
                if index < 2:
                    index += 2
                else:
                    index -= 2
            elif pov == 'left':
                index = index - 1 if index > 0 else 3
            elif pov == 'right':
                index = index + 1 if index < 3 else 0
        # center is to pov of the obj
        elif subj == self.centerReferences[-1]:
            # back is dont care
            if pov == 'front':
                if index < 2:
                    index += 2
                else:
                    index -= 2
            elif pov == 'left':
                index = index + 1 if index < 3 else 0
            elif pov == 'right':
                index = index - 1 if index > 0 else 3

        return self.validPOVs[index]
